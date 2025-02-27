#pragma once
#include "UI/MessageWindow.h"
#include "UI/CommandWindow.h"

#include "Debug/DebugLog.h"


namespace UI {
namespace Battle {
// バトル関係のUIをまとめて持つマネージャー
class BattleUIManager
{
public:
    BattleUIManager() { Debug::debugLog("BattleUIManager()"); }
    MessageWindow& messageWin() { return _message_win; }
    CommandWindow& commandWin() { return _command_win; }

    void update()
    {
        _message_win.update();
        _command_win.update();
    }

    void draw()
    {
        _message_win.draw();
        _command_win.draw();
    }

private:
    MessageWindow _message_win;
    CommandWindow _command_win;
};
}}  // namespace UI::Battle