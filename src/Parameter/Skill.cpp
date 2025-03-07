#include "Parameter/Skill.h"


namespace Parameter {
namespace Skill {

// todo 外部から情報を得られるようにする。
void SkillParameter::makeParameter(ESkillId::Enum id)
{
    switch(id)
    {
        case ESkillId::Enum::NormalAttack:
            _name = "通常攻撃";
            _skill_type = ESkillType::Enum::NormalAttack;
            _skill_target = ESkillTarget::Enum::EnemyOne;
        break;

        case ESkillId::Enum::SkillAttack1:
            _name = "攻撃スキル1";
            _skill_type = ESkillType::Enum::SkillAttack1;
            _skill_target = ESkillTarget::Enum::EnemyOne;
        break;

        case ESkillId::Enum::SkillHeal1:
            _name = "回復スキル1";
            _skill_type = ESkillType::Enum::SkillHeal1;
            _skill_target = ESkillTarget::Enum::PlayableOne;
        break;

        default:
            Debug::assertLog("not use id");
            _name = "None";
            _skill_type = ESkillType::Enum::None;
            _skill_target = ESkillTarget::Enum::None;
        break;
    }
}

}}  // namespace Parameter::Skill