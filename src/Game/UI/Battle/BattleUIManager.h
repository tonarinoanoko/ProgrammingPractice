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
    MessageWindow& messageWindow() { return _message_window; }
    CommandWindow& commandWindw() { return _command_window; }

    void update()
    {
        _message_window.update();
        _command_window.update();
    }

    void draw()
    {
        _message_window.draw();
        _command_window.draw();
    }

private:
    MessageWindow _message_window;
    CommandWindow _command_window;
};
}}  // namespace UI::Battle