#pragma once
#include <memory>
#include "Character/Character.h"
#include "UI/CommandWindow.h"

namespace UI {
namespace Battle {
class BattleTargetSelectWin : public CommandWindow
{
public:
    BattleTargetSelectWin() :
        CommandWindow(10, 200, 80, 100)
    {
    }

    void setTargets(std::vector<std::shared_ptr<Character::CharacterData>> const& targets)
    {
        _targets = targets;
        std::vector<std::string> comands;
        for(int i = 0; i < targets.size(); ++i) {
            comands.emplace_back(targets[i]->name());
        }
        setCommands(comands);
    }

    int selectTargetCharacterId()
    {
        int target = selectedIndex();
        return _targets[target]->characterId();
    }


private:
    std::vector<std::shared_ptr<Character::CharacterData>> _targets;
};
}}  // namespace UI::Battle
