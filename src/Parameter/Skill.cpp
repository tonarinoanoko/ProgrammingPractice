#include "Parameter/Skill.h"


namespace Parameter {
namespace Skill {

// todo 現在は即値だけれど外にパラメーターを用意して対応したいね
ParameterData Parameters::makeParameterData(ESkillId::Enum id)
{
    switch(id)
    {
        case ESkillId::Enum::NormalAttack:
            return { "通常攻撃", ESkillType::Enum::NormalAttack, ESkillTarget::Enum::EnemyOne };
        break;

        case ESkillId::Enum::SkillAttack1:
            return { "攻撃スキル1", ESkillType::Enum::SkillAttack1, ESkillTarget::Enum::EnemyOne };
        break;

        case ESkillId::Enum::SkillHeal1:
            return { "回復スキル1", ESkillType::Enum::SkillHeal1, ESkillTarget::Enum::PlayableOne };
        break;

        default:
            Debug::assertLog("not use id");
            return { "None", ESkillType::Enum::None, ESkillTarget::Enum::None };
        break;
    }
}

}}  // namespace Parameter::Skill