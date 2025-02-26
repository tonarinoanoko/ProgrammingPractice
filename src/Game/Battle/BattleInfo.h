#pragma once
#include "Character/Character.h"
#include "Party/PlayableParty.h"
#include "Party/EnemyParty.h"
#include "Party/BotParty.h"
#include "ActionTimeLine.h"

#include "Debug/DebugLog.h"


namespace Battle {
class BattleInfo {
public:
    BattleInfo() { Debug::debugLog("BattleInfo()"); }

    PlayableParty& playerParty() { return _player_party; }
    EnemyParty& enemyParty() { return _enemy_party; }
    BotParty& botParty() { return _bot_party; }

private:
    PlayableParty _player_party;
    EnemyParty _enemy_party;
    BotParty _bot_party;
};
}  // Battle
