#pragma once
#include "BattlePartyBase.h"
#include "Character/Playable.h"


namespace Battle {
class PlayableParty : public BattlePartyBase
{
public:
    PlayableParty() { Debug::debugLog("PlayableParty()"); }
    void somePlayerSpecificFunction() {
        for (auto& member : _members) {
            auto playable = std::static_pointer_cast<Character::PlayableData>(member);
        }
    }
};
}  // Battle
