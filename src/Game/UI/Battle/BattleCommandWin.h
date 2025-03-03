#pragma once
#include "UI/CommandWindow.h"
#include "Enum/EBattleCommand.h"


namespace UI {
namespace Battle {
class BattleComandWin : public CommandWindow
{
public:
    BattleComandWin() :
        CommandWindow(10, 200, 80, 100)
    {
    }

    EBattleCommand::Enum selectedCommand()
    {
        return static_cast<EBattleCommand::Enum>(selectedIndex());
    }
};
}}  // namespace UI::Battle
