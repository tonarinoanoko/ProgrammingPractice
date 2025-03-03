#include "BattleManager.h"
#include "DxLib.h"
#include "System/InputManager.h"
#include "Battle/Skill/SkillFactory.h"

#include "Battle/Calc/Damage.h"
#include "Debug/DebugLog.h"


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
            new_entry._character_id = member->caracterId();
            new_entry._action_time = member->startActionTime();
            new_entry._cool_time = member->status().statusInt(EStatus::Enum::Spd);
            _action_time_line.addAction(new_entry);
        }
    };
    ActionEntry(enemy_party);
    ActionEntry(player_party);

    _state = EState::UpdateTimeLine;
}

bool BattleManager::isFinishedBattle()
{
    if(_state == EState::None) {
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

    switch(_state) {
        case EState::UpdateTimeLine:
        if(_action_time_line.update()) {
            auto const & chara_data = _battle_info.characterData(_action_time_line.actionEntry()._character_id);
            _message_manager.set(chara_data->name() + "の行動開始");
            _state = EState::StartAction;
        }
        break;

        case EState::StartAction:
        {
            auto const & input = System::InputManager::instance();
            if(input.isKeyDown(KEY_INPUT_Z)) {
                auto const & chara_data = _battle_info.characterData(_action_time_line.actionEntry()._character_id);
                if(chara_data->characterType() == ECharacterType::Enum::Playable) {
                    _pre_command = -1;
                    auto& command_window = _ui_manager->commandWin();
                    command_window.setCommands({"攻撃", "スキル", "防御"});
                    command_window.resetIndex();
                    command_window.setDrawingComand(true);
                    _state = EState::SelectCommand;
                    Debug::debugLog("next state SelectCommand");
                }
                else {
                    _state = EState::EnemyCommand;
                    Debug::debugLog("next state EnemyCommand");
                }
            }
        }
        break;

        case EState::SelectCommand:
        {
        auto& command_window = _ui_manager->commandWin();
        if(command_window.selectedCommand() != _pre_command) {
            switch(command_window.selectedCommand()) {
                case 0:
                _message_manager.set("攻撃を行います");
                break;
                case 1:
                _message_manager.set("スキルを選択します");
                break;
                case 2:
                _message_manager.set("防御を行います");
                break;
            }
            _pre_command = command_window.selectedCommand();
        }

        auto const & input = System::InputManager::instance();
        if(input.isKeyDown(KEY_INPUT_Z)) {
            _message_manager.set("対象を選択してください");
            _pre_command = -1;
            command_window.setDrawingComand(false);

            auto & target_select_window = _ui_manager->targetSelectWin();
            target_select_window.setTargets(_battle_info.enemyParty().getMembers());
            target_select_window.setDrawingComand(true);
            _state = EState::SelectTarget;
            Debug::debugLog("next state SelectTarget");
        }
        }
        break;

        case EState::SelectTarget:
        {
        auto & target_select_window = _ui_manager->targetSelectWin();
        auto const & input = System::InputManager::instance();
        if(input.isKeyDown(KEY_INPUT_Z)) {
            target_select_window.setDrawingComand(false);
            _state = EState::UpdateSkill;
            Debug::debugLog("next state UpdateSkill");
        }
        else if(input.isKeyDown(KEY_INPUT_X)) {
            _ui_manager->commandWin().setDrawingComand(true);
            target_select_window.setDrawingComand(false);
            _state = EState::SelectCommand;
            Debug::debugLog("next state SelectCommand");
        }

        }
        break;

        case EState::EnemyCommand:
        {
        auto const & chara_data = _battle_info.characterData(_action_time_line.actionEntry()._character_id);
        _message_manager.set(chara_data->name() + "の行動");
        _state = EState::EraseTimeLine;
        Debug::debugLog("next state EraseTimeLine");
        }
        break;

        case EState::UpdateSkill:
        {
        auto const& actor = _battle_info.characterData(_action_time_line.actionEntry()._character_id);
        auto & target = _battle_info.enemyParty().getMemberFromCharacterId(_ui_manager->targetSelectWin().selectTargetCharacterId());
        auto damage = Calc::damage(*actor.get(), *target.get());
        target->damage(damage);

        _message_manager.set(actor->name() + "の攻撃！\n" + target->name() + "に" + std::to_string(damage) + "のダメージ！");

        _state = EState::EraseTimeLine;
        Debug::debugLog("next state EraseTimeLine");
        }
        break;

        case EState::EraseTimeLine:
        {
        auto const & input = System::InputManager::instance();
        if(input.isKeyDown(KEY_INPUT_Z)) {
            auto const& entry = _action_time_line.actionEntry();

            ActionTimeLine::ActionEntry new_entry {entry._character_id, 100, 10};
            _action_time_line.eraseAction(entry._character_id);

            _action_time_line.addAction(new_entry);  // 新規の行動を追加する。
            _state = EState::UpdateTimeLine;
            Debug::debugLog("next state UpdateTimeLine");
        }
        }
        break;
    }
}
}  // Battle
