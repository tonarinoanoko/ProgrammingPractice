#pragma once
#include "ParameterInc.h"

namespace Parameter {
// 各パラメーターのinstanceを呼んでおく
inline void initParameter() {
    Skill::instance();
    Monster::instance();
}
}  // namespace Parameter
