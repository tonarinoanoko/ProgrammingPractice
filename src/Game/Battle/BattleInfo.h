#pragma once
#include "Character/Character.h"
#include "PlayableParty.h"
#include "EnemyParty.h"


namespace Battle {
class BattleInfo {
public:
    BattleInfo() {};

    void nextTurn() {}  // ターンを進める
    bool isBattleOver() const { return false; }  // 勝敗判定
    
    PlayableParty& playerParty() { return _player_party; }
    EnemyParty& enemyParty() { return _enemy_party; }

private:
    PlayableParty _player_party;
    EnemyParty _enemy_party;
    int _turn_count = 0;  // バトルのターン数
};
}  // Battle
