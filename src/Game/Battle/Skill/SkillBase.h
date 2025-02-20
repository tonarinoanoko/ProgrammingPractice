#pragma once

namespace Battle {
namespace Skill {
class SkillBase
{
public:
    SkillBase() {}

    virtual void update() = 0;
    virtual void execute() = 0;
    virtual bool isFinished() = 0;
};

}}  // namespace Battle::Skill
