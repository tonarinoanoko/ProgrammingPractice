#pragma once

namespace EStatus {

enum class Enum
{
    Hp,
    Atk,
    Def,
    Spd,

    Max
};

inline int max() {
    return static_cast<int>(Enum::Max);
}

}
