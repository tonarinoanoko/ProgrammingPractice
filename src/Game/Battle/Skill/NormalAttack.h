#pragma once
#include "SkillBase.h"
#include "SkillFactory.h"


namespace Battle {
namespace Skill {
class NormalAttack : public SkillBase
{
public:
    void update() override {}
    void execute() override {}
    bool isFinished() override { return false; }
};
}}  // namespace Battle::Skill
