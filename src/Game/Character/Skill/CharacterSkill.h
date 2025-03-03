#pragma once
#include "Enum/ESkillId.h"
#include "Enum/ESkillType.h"
#include "Parameter/Skill.h"


namespace Character {
namespace Skill {
class SkillData
{
public:
    SkillData() {};
    SkillData(ESkillId::Enum id) :
    _skill_id(id)
    {
        // todo パラメータからskilltypeを取得
        auto const& param = Parameter::Skill::Parameters::instance();
        _skill_type = param.parameter(_skill_id).skillType();
    }

private:
    ESkillId::Enum _skill_id;
    ESkillType::Enum _skill_type;
};
}}  // namespace Character::Skill