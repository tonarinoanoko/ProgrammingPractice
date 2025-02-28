#pragma once


namespace UI {
namespace Battle {
class BattleTargetSelectWin : public CommandWindow
{
public:
    BattleTargetSelectWin() :
        CommandWindow(10, 200, 80, 100)
    {
    }
};
}}  // namespace UI::Battle
