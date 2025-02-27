#pragma once


namespace EBattleCommand {

enum class Enum
{
    None,
    NormalAttack,
    Skill,
    Defense,

    Max
};

inline int max() {
    return static_cast<int>(Enum::Max);
}

}
