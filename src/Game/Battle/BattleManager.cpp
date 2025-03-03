#include "BattleManager.h"
#include "DxLib.h"
#include "System/InputManager.h"
#include "Battle/Skill/SkillFactory.h"

#include "Battle/Calc/Damage.h"
#include "Debug/GameDebug.h"


namespace Battle {

Character::UStatusMap makeStatusMap()
{
    auto status_map = Character::UStatusMap();
    status_map[EStatus::Enum::Hp].set(100);
    status_map[EStatus::Enum::Atk].set(10);
    status_map[EStatus::Enum::Spd].set(10);
    return status_map;
}

int BattleManager::makeNewCharacterId()
{
    ++_use_character_id;
    return _use_character_id;
}

void BattleManager::startBattle(UI::Battle::BattleUIManager* ui_manager)
{
    // ここでインスタンスを呼び出してコンストラクタを通しておく
    Skill::SkillFactory::instance();

    _use_character_id = 0;

    Debug::assertLog(ui_manager, "ui_manager is null");
    _ui_manager = ui_manager;
    auto status = Character::Status();
    status.setStatus(makeStatusMap());

    auto& enemy_party = _battle_info.enemyParty();
    auto new_enemy = std::make_shared<Character::EnemyData>();
    status.statusValue(EStatus::Enum::Hp).add(10);
    new_enemy->setName("すらいむ");
    new_enemy->setCharacterId(makeNewCharacterId());
    new_enemy->setStatus(status);
    enemy_party.addMember(new_enemy);

    auto& player_party = _battle_info.playerParty();
    auto new_playable = std::make_shared<Character::PlayableData>();
    status.statusValue(EStatus::Enum::Hp).add(10);
    new_playable->setName("ゆうしゃ");
    new_playable->setCharacterId(makeNewCharacterId());
    new_playable->setStatus(status);
    player_party.addMember(new_playable);

    // 初期行動順の対応
    auto ActionEntry = [&](Battle::BattlePartyBase const& party)
    {
        ActionTimeLine::ActionEntry new_entry {0, 0, 0};
        for(auto const& member : party.getMembers()) {
            new_entry._character_id = member->characterId();
            new_entry._action_time = member->startActionTime();
            new_entry._cool_time = member->status().statusInt(EStatus::Enum::Spd);
            _action_time_line.addAction(new_entry);
        }
    };
    ActionEntry(enemy_party);
    ActionEntry(player_party);

    _state.change(EState::UpdateTimeLine);
}

bool BattleManager::isFinishedBattle()
{
    if(_state.current() == EState::None) {
        return false;
    }

    auto const& p_party = _battle_info.playerParty();
    auto const& e_party = _battle_info.enemyParty();

    return p_party.isAnnihilation() || e_party.isAnnihilation();
}

void BattleManager::update()
{
    Debug::assertLog(_ui_manager, "ui manager null");
    if(_ui_manager == nullptr) {
        return;
    }

    _state.update();
    switch(_state.current()) {
        case EState::UpdateTimeLine:
        if(_state.changed()) {
            Debug::debugLog("State UpdateTimeLine");
        }

        if(_action_time_line.update()) {
            _state.change(EState::StartAction);
        }
        break;

        case EState::StartAction:
        {
            if(_state.changed()) {
                auto const & chara_data = _battle_info.characterData(_action_time_line.actionEntry()._character_id);
                _message_manager.set(chara_data->name() + "の行動開始");

                Debug::debugLog("State StartAction");
            }

            auto const & input = System::InputManager::instance();
            if(input.isKeyDown(KEY_INPUT_Z)) {
                auto const & chara_data = _battle_info.characterData(_action_time_line.actionEntry()._character_id);
                if(chara_data->characterType() == ECharacterType::Enum::Playable) {
                    _state.change(EState::SelectCommand);
                }
                else {
                    _state.change(EState::EnemyCommand);
                }
            }
        }
        break;

        case EState::SelectCommand:
        {
        auto& command_window = _ui_manager->commandWin();
        if(_state.changed()) {
            _pre_command = EBattleCommand::Enum::None;
            command_window.setCommands({"攻撃", "スキル", "防御"});
            command_window.resetIndex();
            command_window.setDrawingComand(true);

            Debug::debugLog("State SelectCommand");
        }

        if(command_window.selectedCommand() != _pre_command) {
            switch(command_window.selectedCommand()) {
                case EBattleCommand::Enum::NormalAttack:
                _message_manager.set("攻撃を行います");
                break;
                case EBattleCommand::Enum::Skill:
                _message_manager.set("スキルを選択します");
                break;
                case EBattleCommand::Enum::Defense:
                _message_manager.set("防御を行います");
                break;
            }
            _pre_command = command_window.selectedCommand();
        }

        auto const & input = System::InputManager::instance();
        if(input.isKeyDown(KEY_INPUT_Z)) {
            command_window.setDrawingComand(false);
            _state.change(EState::SelectTarget);
        }
        }
        break;

        case EState::SelectTarget:
        {
        auto & target_select_window = _ui_manager->targetSelectWin();
        if(_state.changed()) {
            _message_manager.set("対象を選択してください");
            target_select_window.setTargets(_battle_info.enemyParty().getMembers());
            target_select_window.setDrawingComand(true);

            Debug::debugLog("State SelectTarget");
        }

        auto const & input = System::InputManager::instance();
        if(input.isKeyDown(KEY_INPUT_Z)) {
            target_select_window.setDrawingComand(false);
            _target_character_id = _ui_manager->targetSelectWin().selectTargetCharacterId();
            _state.change(EState::UpdateSkill);
        }
        else if(input.isKeyDown(KEY_INPUT_X)) {
            _ui_manager->commandWin().setDrawingComand(true);
            target_select_window.setDrawingComand(false);
            _state.change(EState::SelectCommand);
        }

        }
        break;

        case EState::EnemyCommand:
        {
        if(_state.changed()) {
            auto const & chara_data = _battle_info.characterData(_action_time_line.actionEntry()._character_id);

            // todo とりあえず0番目のターゲット
            auto const & p_party = _battle_info.playerParty();
            _target_character_id = p_party.getMember(0)->characterId();

            _state.change(EState::UpdateSkill);
            Debug::debugLog("State EnemyCommand");
        }
        }
        break;

        case EState::UpdateSkill:
        {
        if(_state.changed()) {

            auto const& actor = _battle_info.characterData(_action_time_line.actionEntry()._character_id);
            auto & target = _battle_info.characterData(_target_character_id);

            auto skill = Skill::SkillFactory::instance().create(ESkillType::Enum::NormalAttack);
            auto augument = Skill::SkillBase::Argument { *actor, *target, _message_manager };
            skill->execute(augument);

            Debug::debugLog("State UpdateSkill");
        }

        auto const & input = System::InputManager::instance();
        if(input.isKeyDown(KEY_INPUT_Z)) {
            _state.change(EState::EraseTimeLine);
        }
        }
        break;

        case EState::EraseTimeLine:
        {
            Debug::debugLog("State EraseTimeLine");

            auto const& entry = _action_time_line.actionEntry();

            auto const& actor = _battle_info.characterData(entry._character_id);
            ActionTimeLine::ActionEntry new_entry {actor->characterId(), 100, actor->status().statusInt(EStatus::Enum::Spd)};

            _action_time_line.eraseAction(entry._character_id);
            _action_time_line.addAction(new_entry);
            _state.change(EState::UpdateTimeLine);
        }
        break;
    }
}
}  // Battle
