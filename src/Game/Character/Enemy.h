#pragma once
#include "Character.h"

namespace Character {
class EnemyData : public CharacterData
{
public:
    EnemyData()
    : CharacterData(ECharacterType::Enum::Enemy)
    {
    }
};
}  // Character
