#pragma once
#include "BattlePartyBase.h"
#include "Character/Enemy.h"


namespace Battle {
class EnemyParty : public BattlePartyBase
{
public:
    EnemyParty() {}
    void somePlayerSpecificFunction() {
        for (auto& member : _members) {
            auto enemy = std::static_pointer_cast<Character::EnemyData>(member);
        }
    }
};
}  // Battle
