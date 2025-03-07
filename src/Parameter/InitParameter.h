#pragma once
#include "Skill.h"
#include "Monster.h"

namespace Parameter {
// 各パラメーターのinstanceを呼んでおく
inline void initParameter() {
    Skill::instance();
    Monster::instance();
}
}  // namespace Parameter
