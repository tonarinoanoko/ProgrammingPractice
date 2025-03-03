#pragma once
#include "Character/Character.h"
#include "Common/MessageManager.h"


namespace Battle {
namespace Skill {
class SkillBase
{
public:
    struct Argument
    {
    public:
        Character::CharacterData & actor;
        Character::CharacterData & target;
        Common::MessageManager & message_manager;
    };

public:
    SkillBase() {}
    virtual void execute(Argument& argument) = 0;
};

}}  // namespace Battle::Skill
