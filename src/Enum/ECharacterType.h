#pragma once


namespace ECharacterType {

enum class Enum
{
    None,
    Playable,
    Enemy,
    Bot,

    Max
};

inline int max() {
    return static_cast<int>(Enum::Max);
}

}
