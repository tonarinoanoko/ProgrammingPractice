#pragma once
#include "BattlePartyBase.h"
#include "Character/Bot.h"


namespace Battle {
class BotParty : public BattlePartyBase
{
public:
    BotParty() { Debug::debugLog("BotParty()"); }
    void somePlayerSpecificFunction() {
        for (auto& member : _members) {
            auto enemy = std::static_pointer_cast<Character::BotData>(member);
        }
    }
};
}  // Battle
