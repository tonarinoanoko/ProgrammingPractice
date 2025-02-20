#pragma once

namespace Battle {
namespace Skill {
class SkillBase
{
public:
    SkillBase() {}

    virtual void update();
    virtual void execute();
    virtual bool isFinished();
};

}}  // namespace Battle::Skill
