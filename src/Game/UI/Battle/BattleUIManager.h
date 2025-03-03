#pragma once
#include "UI/MessageWindow.h"
#include "UI/Battle/BattleCommandWin.h"
#include "UI/Battle/BattleTargetSelectWin.h"
#include "UI/Battle/BatleSkillSelectWin.h"

#include "Debug/DebugLog.h"


namespace UI {
namespace Battle {
// バトル関係のUIをまとめて持つマネージャー
class BattleUIManager
{
public:
    BattleUIManager() {}
    MessageWindow& messageWin() { return _message_win; }
    BattleComandWin& commandWin() { return _command_win; }
    BattleTargetSelectWin& targetSelectWin() { return _target_select_win; }
    BattleSkillSelectWin& skillSelectWin() { return _skill_select_win; }

    void update()
    {
        _message_win.update();
        _command_win.update();
        _target_select_win.update();
        _skill_select_win.update();
    }

    void draw()
    {
        _message_win.draw();
        _command_win.draw();
        _target_select_win.draw();
        _target_select_win.draw();
    }

private:
    MessageWindow _message_win;
    BattleComandWin _command_win;
    BattleTargetSelectWin _target_select_win;
    BattleSkillSelectWin _skill_select_win;
};
}}  // namespace UI::Battle