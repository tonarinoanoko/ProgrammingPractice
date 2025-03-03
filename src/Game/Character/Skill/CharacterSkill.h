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
    }

    ESkillId::Enum skillId() const { return _skill_id; }

private:
    ESkillId::Enum _skill_id;
    // ESkillType::Enum _skill_type;  // スキルタイプはパラメーターから取得できる
};
}}  // namespace Character::Skill