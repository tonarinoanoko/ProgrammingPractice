#pragma once

namespace EScene {

enum class Enum
{
    None = 0,
    Main,
    Battle,

    Max
};

inline int max() {
    return static_cast<int>(Enum::Max);
}

}
