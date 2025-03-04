#pragma once
#include "SkillBase.h"


namespace Battle {
namespace Skill {
class SkillHeal1 : public SkillBase
{
public:
    void execute(Argument& argument) override;
    int actionTime() override { return 200; }
};
}}  // namespace Battle::Skill
