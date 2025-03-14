#pragma once
#include "System/Image.h"
#include "UI/MessageWindow.h"
#include "UI/Battle/BattleCommandWin.h"
#include "UI/Battle/BattleTargetSelectWin.h"
#include "UI/Battle/BatleSkillSelectWin.h"
#include "UI/Battle/ActionTimeLineUI.h"

#include "Debug/DebugLog.h"


namespace UI {
namespace Battle {
// バトル関係のUIをまとめて持つマネージャー
class BattleUIManager
{
public:
    BattleUIManager() {
        _image_bg.load("resource/BG/bg_1.png");
    }

    MessageWindow& messageWin() { return _message_win; }
    BattleComandWin& commandWin() { return _command_win; }
    BattleTargetSelectWin& targetSelectWin() { return _target_select_win; }
    BattleSkillSelectWin& skillSelectWin() { return _skill_select_win; }
    ActionTimeLineUI& actionTimeLine() { return _time_line; }

    void update()
    {
        _message_win.update();
        _command_win.update();
        _target_select_win.update();
        _skill_select_win.update();
    }

    void draw()
    {
        _image_bg.draw(0, 0);
        _message_win.draw();
        _command_win.draw();
        _target_select_win.draw();
        _skill_select_win.draw();
        _time_line.draw();
    }

private:
    MessageWindow _message_win;
    BattleComandWin _command_win;
    BattleTargetSelectWin _target_select_win;
    BattleSkillSelectWin _skill_select_win;
    ActionTimeLineUI _time_line;
    System::Image _image_bg;
};
}}  // namespace UI::Battle