#pragma once
#include "UI/CommandWindow.h"


namespace UI {
namespace Battle {
class BattleComandWin : public CommandWindow
{
public:
    BattleComandWin() :
        CommandWindow(10, 200, 80, 100)
    {
    }
};
}}  // namespace UI::Battle
