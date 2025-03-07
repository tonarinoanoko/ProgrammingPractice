#pragma once
#include "Enum/ESkillId.h"
#include "Parameter/Skill.h"
#include "Character/Character.h"
#include "UI/CommandWindow.h"

#include "Debug/GameDebug.h"


namespace UI {
namespace Battle {
class BattleSkillSelectWin : public CommandWindow
{
public:
    BattleSkillSelectWin() :
        CommandWindow(10, 200, 80, 100)
    {
    }

    void setActorSkill(Character::CharacterData const& actor)
    {
        _targets.clear();
        std::vector<std::string> commands;
        auto const & skills = actor.skills();
        for(int i = 0; i < skills.size(); ++i) {
            auto param = Parameter::Skill::instance().parameter(skills[i].skillId());
            commands.emplace_back(param._name);
            _targets.emplace_back(skills[i].skillId());
        }

        setCommands(commands);
    }

    ESkillId::Enum selectSkillId()
    {
        int target = selectedIndex();
        return _targets[target];
    }


private:
    std::vector<ESkillId::Enum> _targets;
};
}}  // namespace UI::Battle
