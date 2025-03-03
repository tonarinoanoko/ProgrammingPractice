#pragma once
#include "SkillBase.h"


namespace Battle {
namespace Skill {
class NormalAttack : public SkillBase
{
public:
    void execute(Argument& argument) override;
    int actionTime() override { return 100; }
};
}}  // namespace Battle::Skill
