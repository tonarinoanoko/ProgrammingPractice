#pragma once
#include "BattlePartyBase.h"
#include "Character/Playable.h"


class PlayableParty : public BattlePartyBase {
public:
    void SomePlayerSpecificFunction() {
        for (auto& member : _members) {
            auto playable = std::static_pointer_cast<Character::PlayableData>(member);
            //playable->SomePlayableMethod();
        }
    }
};
