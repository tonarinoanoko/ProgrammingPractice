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

    void setCommands(std::vector<EBattleCommand::Enum> const& commands)
    {
        _targets = commands;
        CommandWindow::setCommands({"攻撃", "スキル", "防御"});
    }

    EBattleCommand::Enum selectedCommand()
    {
        return _targets[selectedIndex()];
    }

private:
    std::vector<EBattleCommand::Enum> _targets;
};
}}  // namespace UI::Battle
