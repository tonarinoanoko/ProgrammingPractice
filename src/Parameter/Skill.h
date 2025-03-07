// Skill.h
#pragma once
#include "ParameterBase.h"
#include "Enum/ESkillId.h"
#include "Enum/ESkillType.h"
#include "Enum/ESkillTarget.h"


namespace Parameter {
namespace Skill {
// Skillに対応するパラメータを定義
class SkillParameter : public ParameterBase<ESkillId::Enum>
{
public:
    std::string _name;
    ESkillType::Enum _skill_type;
    ESkillTarget::Enum _skill_target;

    void makeParameter(ESkillId::Enum id) override;
};

inline auto& instance() {
    return Parameters<ESkillId::Enum, Parameter::Skill::SkillParameter>::instance();
}

}  // namespace Skill
}  // namespace Parameter
