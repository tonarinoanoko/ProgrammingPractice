#pragma once
#include "Enum/ESkillId.h"
#include "Enum/ESkillType.h"


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
    }

private:
    ESkillId::Enum _skill_id;
    ESkillType::Enum _skill_type;
};
}}  // namespace Character::Skill