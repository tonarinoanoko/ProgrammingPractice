#pragma once
#include "SkillBase.h"


namespace Battle {
namespace Skill {
class SkillAttack1 : public SkillBase
{
public:
    void execute(Argument& argument) override;
    int actionTime() override { return 150; }
};
}}  // namespace Battle::Skill
