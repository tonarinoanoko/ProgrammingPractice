#pragma once
#include "Character/Character.h"
#include "PlayableParty.h"
#include "EnemyParty.h"
#include "BotParty.h"
#include "ActionTimeLine.h"

#include "Debug/DebugLog.h"


namespace Battle {
class BattleInfo {
public:
    BattleInfo() {Debug::debugLog("BattleInfo");};

    bool isBattleOver() const { return false; }  // 勝敗判定

    PlayableParty& playerParty() { return _player_party; }
    EnemyParty& enemyParty() { return _enemy_party; }
    BotParty& botParty() { return _bot_party; }

private:
    PlayableParty _player_party;
    EnemyParty _enemy_party;
    BotParty _bot_party;
};
}  // Battle
