#pragma once
#include "BattlePartyBase.h"
#include "Character/Enemy.h"


class EnemyParty : public BattlePartyBase {
public:
    void SomePlayerSpecificFunction() {
        for (auto& member : _members) {
            auto enemy = std::static_pointer_cast<Character::EnemyData>(member);
            //playable->SomePlayableMethod();
        }
    }
};
