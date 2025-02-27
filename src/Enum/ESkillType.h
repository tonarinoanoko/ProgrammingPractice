#pragma once


namespace ESkillType {

enum class Enum
{
    None,
    NormalAttack,

    Max
};

inline int max() {
    return static_cast<int>(Enum::Max);
}

}
