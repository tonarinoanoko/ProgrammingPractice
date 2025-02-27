#pragma once
#include "Character.h"

namespace Character {
class BotData : public CharacterData
{
public:
    BotData()
    : CharacterData(ECharacterType::Enum::Bot)
    {
    }
};
}  // Character
