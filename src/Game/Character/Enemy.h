#pragma once
#include <memory>
#include "Character.h"
#include "Parameter/Monster.h"


namespace Character {
class EnemyData : public CharacterData
{
public:
    EnemyData()
    : CharacterData(ECharacterType::Enum::Enemy)
    {
    }
};

std::shared_ptr<Character::EnemyData> makeEnemy(EMonsterId::Enum id);

}  // Character
