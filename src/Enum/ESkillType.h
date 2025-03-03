#pragma once


namespace ESkillType {

enum class Enum
{
    None,
    NormalAttack,
    SkillAttack1,

    Max
};

inline int max() {
    return static_cast<int>(Enum::Max);
}

}
