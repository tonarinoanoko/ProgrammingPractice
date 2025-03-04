#pragma once


namespace ESkillTarget {

enum class Enum
{
    None,
    EnemyOne,
    EnemyAll,

    PlayableOne,
    PlayableAll,

    Me,

    Max
};

inline int max() {
    return static_cast<int>(Enum::Max);
}

}