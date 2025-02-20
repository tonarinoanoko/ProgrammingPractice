#include "BattleManager.h"


namespace Battle {

Character::UStatusMap makeStatusMap()
{
    auto status_map = Character::UStatusMap();
    status_map[EStatus::Enum::Hp].set(100);
    return status_map;
}

void BattleManager::startBattle()
{
    auto status = Character::Status();
    status.setStatus(makeStatusMap());

    auto enemy_party = _battle_info.enemyParty();
    auto new_enemy = std::make_shared<Character::EnemyData>();
    status.statusValue(EStatus::Enum::Hp).add(10);
    new_enemy->setStatus(status);
    enemy_party.addMember(new_enemy);

    auto player_party = _battle_info.playerParty();
    auto new_playable = std::make_shared<Character::PlayableData>();
    status.statusValue(EStatus::Enum::Hp).add(10);
    new_playable->setStatus(status);
    player_party.addMember(new_playable);
}

void BattleManager::updateOneTrun()
{
    if(_action_time_line.update() == false) {
        return;
    }

    auto const& entry = _action_time_line.actionEntry();

    // 行動の更新

    _action_time_line.eraseAction(entry._character_id);
    ActionTimeLine::ActionEntry new_entry;
    _action_time_line.addAction(new_entry);  // 新規の行動を追加する。
}
}  // Battle
