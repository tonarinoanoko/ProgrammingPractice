#include "BattleManager.h"
#include "DxLib.h"
#include "System/InputManager.h"

#include "Debug/DebugLog.h"


namespace Battle {

Character::UStatusMap makeStatusMap()
{
    auto status_map = Character::UStatusMap();
    status_map[EStatus::Enum::Hp].set(100);
    return status_map;
}

void BattleManager::startBattle(UI::Battle::BattleUIManager* ui_manager)
{
    Debug::assertLog(ui_manager, "ui_manager is null");
    _ui_manager = ui_manager;
    auto status = Character::Status();
    status.setStatus(makeStatusMap());

    auto& enemy_party = _battle_info.enemyParty();
    auto new_enemy = std::make_shared<Character::EnemyData>();
    status.statusValue(EStatus::Enum::Hp).add(10);
    new_enemy->setName("enemy 1");
    new_enemy->setStatus(status);
    enemy_party.addMember(new_enemy);

    auto& player_party = _battle_info.playerParty();
    auto new_playable = std::make_shared<Character::PlayableData>();
    status.statusValue(EStatus::Enum::Hp).add(10);
    new_playable->setName("playable 1");
    new_playable->setStatus(status);
    player_party.addMember(new_playable);

    // 初期行動順の対応
    ActionTimeLine::ActionEntry new_entry {0, 5, 1};
    _action_time_line.addAction(new_entry);  // 新規の行動を追加する。

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

    auto const & input = System::InputManager::instance();
    switch(_state) {
        case EState::UpdateTimeLine:
        if(_action_time_line.update()) {
            _ui_manager->commandWindw().setDrawingComand(true);
            _state = EState::UpdateCommand;
            Debug::debugLog("next state UpdateCommand");
        }
        break;

        case EState::UpdateCommand:
        if(input.isKeyDown(KEY_INPUT_C)) {
            _ui_manager->commandWindw().setDrawingComand(false);
            _state = EState::UpdateSkill;
            Debug::debugLog("next state UpdateSkill");
        }
        break;

        case EState::UpdateSkill:
        _state = EState::EraseTimeLine;
        Debug::debugLog("next state EraseTimeLine");
        break;

        case EState::EraseTimeLine:
        auto const& entry = _action_time_line.actionEntry();
        _action_time_line.eraseAction(entry._character_id);
        ActionTimeLine::ActionEntry new_entry {0, 5, 1};
        _action_time_line.addAction(new_entry);  // 新規の行動を追加する。
        _state = EState::UpdateTimeLine;
        Debug::debugLog("next state UpdateTimeLine");
        break;
    }
}
}  // Battle
