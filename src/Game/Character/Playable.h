#pragma once
#include "Character.h"


namespace Character {
class PlayableData : public CharacterData
{
public:
    PlayableData()
    : CharacterData(ECharacterType::Enum::Playable)
    {
    }
};

}  // Character
