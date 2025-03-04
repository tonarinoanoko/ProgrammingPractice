#pragma once


namespace ESkillId {

enum class Enum
{
    None,
    NormalAttack,
    SkillAttack1,
    SkillHeal1,

    Max
};

inline int max() {
    return static_cast<int>(Enum::Max);
}

}
