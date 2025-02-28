#pragma once
#include "UI/CommandWindow.h"


namespace UI {
namespace Battle {
class BattleSkillSelectWin : public CommandWindow
{
public:
    BattleSkillSelectWin() :
        CommandWindow(10, 200, 80, 100)
    {
    }
};
}}  // namespace UI::Battle
