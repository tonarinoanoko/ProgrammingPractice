#pragma once
#include <vector>
#include "Character/Character.h"
#include "Battle/BattleInfo.h"
#include "Common/MessageManager.h"


namespace Battle {
namespace Skill {
class SkillBase
{
public:
    struct Argument
    {
    public:
        BattleInfo & _battle_info;
        int actor;
        std::vector<int> targets;
        Common::MessageManager & message_manager;
    };

public:
    SkillBase() {}
    virtual void execute(Argument& argument) = 0;
};

}}  // namespace Battle::Skill
