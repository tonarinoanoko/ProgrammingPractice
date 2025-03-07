#pragma once
#include "Skill.h"

namespace Parameter {
// 各パラメーターのinstanceを呼んでおく
inline void initParameter() {
    Skill::instance();
}
}  // namespace Parameter