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

    auto skill_data_a = Character::Skill::SkillData(ESkillId::Enum::SkillAttack1);
    auto skill_data_h = Character::Skill::SkillData(ESkillId::Enum::SkillHeal1);

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
    new_playable->addSkill(skill_data_a);
    new_playable->setStatus(status);

    player_party.addMember(new_playable);

    auto new_playable2 = std::make_shared<Character::PlayableData>();
    status.statusValue(EStatus::Enum::Hp).add(10);
    new_playable2->setName("そうりょ");
    new_playable2->setCharacterId(makeNewCharacterId());
    new_playable2->addSkill(skill_data_h);
    new_playable2->setStatus(status);

    player_party.addMember(new_playable2);

    // 初期行動順の対応
    auto ActionEntry = [&](Battle::BattlePartyBase const& party)
    {
        ActionTimeLine::ActionEntry new_entry {0, 0, 0};
        for(auto const& member : party.getMembers()) {
            new_entry._character_id = member->characterId();
            new_entry._action_time = member->startActionTime();
            new_entry._cool_time = member->status().statusInt(EStatus::Enum::Spd);
            _battle_info.actionTimeLine().addAction(new_entry);
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
            UpdateTimeLine();
        break;

        case EState::StartAction:
            StartAction();
        break;

        case EState::SelectCommand:
            SelectCommand();
        break;

        case EState::SelectSkill:
            SelectSkill();
        break;

        case EState::SelectTarget:
            SelectTarget();
        break;

        case EState::EnemyCommand:
            EnemyCommand();
        break;

        case EState::UpdateSkill:
            UpdateSkill();
        break;

        case EState::EraseTimeLine:
            EraseTimeLine();
        break;
    }
}

void BattleManager::UpdateTimeLine()
{
    if(_state.changed()) {
        Debug::debugLog("State UpdateTimeLine");
    }

    if(_battle_info.actionTimeLine().update()) {
        _state.change(EState::StartAction);
    }
}

void BattleManager::StartAction()
{
    if(_state.changed()) {
        Debug::debugLog("State StartAction");

        auto const & chara_data = _battle_info.characterData(_battle_info.actionTimeLine().actionEntry()._character_id);
        _message_manager.set(chara_data->name() + "の行動開始");
    }

    auto const & input = System::InputManager::instance();
    if(input.isKeyDown(KEY_INPUT_Z)) {
        auto const & chara_data = _battle_info.characterData(_battle_info.actionTimeLine().actionEntry()._character_id);
        if(chara_data->characterType() == ECharacterType::Enum::Playable) {
            _state.change(EState::SelectCommand);
        }
        else {
            _state.change(EState::EnemyCommand);
        }
    }
}

void BattleManager::SelectCommand()
{
    auto& command_window = _ui_manager->commandWin();
    if(_state.changed()) {
        Debug::debugLog("State SelectCommand");

        _pre_command = EBattleCommand::Enum::None;
        command_window.setCommands({EBattleCommand::Enum::NormalAttack, EBattleCommand::Enum::Skill, EBattleCommand::Enum::Defense});
        command_window.resetIndex();
        command_window.setDrawingComand(true);
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
        switch(command_window.selectedCommand()) {
            case EBattleCommand::Enum::NormalAttack:
            _use_skill = ESkillId::Enum::NormalAttack;
            _state.change(EState::SelectTarget);
            break;
            case EBattleCommand::Enum::Skill:
            _state.change(EState::SelectSkill);
            break;
            case EBattleCommand::Enum::Defense:
            _use_skill = ESkillId::Enum::NormalAttack;
            _state.change(EState::SelectTarget);
            break;
        }
    }
}

void BattleManager::SelectSkill()
{
    auto & skill_select_window = _ui_manager->skillSelectWin();
    if(_state.changed()) {
        Debug::debugLog("State SelectSkill");

        auto const & actor = _battle_info.characterData(_battle_info.actionTimeLine().actionEntry()._character_id);
        skill_select_window.setActorSkill(*actor);
        skill_select_window.resetIndex();
        skill_select_window.setDrawingComand(true);
    }

    auto const & input = System::InputManager::instance();
    if(input.isKeyDown(KEY_INPUT_Z)) {
        _use_skill = skill_select_window.selectSkillId();
        skill_select_window.setDrawingComand(false);
        _state.change(EState::SelectTarget);
    }
    else if(input.isKeyDown(KEY_INPUT_X)) {
        skill_select_window.setDrawingComand(false);
        _state.change(EState::SelectCommand);
    }
}

void BattleManager::SelectTarget()
{
    auto & target_select_window = _ui_manager->targetSelectWin();
    if(_state.changed()) {
        Debug::debugLog("State SelectTarget");

        _message_manager.set("対象を選択してください");

        auto skill_param = Parameter::Skill::Parameters::instance().parameter(_use_skill);
        if(skill_param.skillTarget() == ESkillTarget::Enum::EnemyOne) {
            target_select_window.setTargets(_battle_info.enemyParty().getMembers());
        }
        else {
            target_select_window.setTargets(_battle_info.playerParty().getMembers());
        }
        target_select_window.setDrawingComand(true);
    }

    auto const & input = System::InputManager::instance();
    if(input.isKeyDown(KEY_INPUT_Z)) {
        target_select_window.setDrawingComand(false);
        _target_character_ids.clear();
        _target_character_ids.emplace_back(_ui_manager->targetSelectWin().selectTargetCharacterId());
        _state.change(EState::UpdateSkill);
    }
    else if(input.isKeyDown(KEY_INPUT_X)) {
        target_select_window.setDrawingComand(false);
        _state.change(EState::SelectCommand);  // todo前の画面に戻る
    }
}

void BattleManager::EnemyCommand()
{
    if(_state.changed()) {
        Debug::debugLog("State EnemyCommand");

        auto const & chara_data = _battle_info.characterData(_battle_info.actionTimeLine().actionEntry()._character_id);

        _use_skill = ESkillId::Enum::NormalAttack;
        // todo とりあえず0番目のターゲット
        auto const & p_party = _battle_info.playerParty();
        _target_character_ids.clear();
        _target_character_ids.emplace_back(p_party.getMember(0)->characterId());

        _state.change(EState::UpdateSkill);
    }
}

void BattleManager::UpdateSkill()
{
    if(_state.changed()) {
        Debug::debugLog("State UpdateSkill");

        auto skill_type = Parameter::Skill::Parameters::instance().parameter(_use_skill).skillType();
        auto skill = Skill::SkillFactory::instance().create(skill_type);
        auto augument = Skill::SkillBase::Argument { _battle_info, _battle_info.actionTimeLine().actionEntry()._character_id, _target_character_ids, _message_manager };
        skill->execute(augument);
        _next_action_time = skill->actionTime();
    }

    auto const & input = System::InputManager::instance();
    if(input.isKeyDown(KEY_INPUT_Z)) {
        _state.change(EState::EraseTimeLine);
    }
}

void BattleManager::EraseTimeLine()
{
    Debug::debugLog("State EraseTimeLine");

    auto & action_time_line = _battle_info.actionTimeLine();
    auto const& entry = action_time_line.actionEntry();

    auto const& actor = _battle_info.characterData(entry._character_id);
    ActionTimeLine::ActionEntry new_entry {actor->characterId(), _next_action_time, actor->status().statusInt(EStatus::Enum::Spd)};

    action_time_line.eraseAction(entry._character_id);
    action_time_line.addAction(new_entry);
    _state.change(EState::UpdateTimeLine);
}

}  // Battle
