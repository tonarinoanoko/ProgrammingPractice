#pragma once
#include "System/Image.h"
#include "UI/MessageWindow.h"
#include "UI/Battle/BattleCommandWin.h"
#include "UI/Battle/BattleTargetSelectWin.h"
#include "UI/Battle/BatleSkillSelectWin.h"
#include "UI/Battle/ActionTimeLineUI.h"
#include "UI/Battle/PlayableInfoUI.h"


#include "Battle/BattleInfo.h"  // toto テスト
using namespace Battle;  // UI::Battle内でBattleを使用しようとしたらエラーになるので仕方なくusingする

#include "Debug/GameDebug.h"


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

    void setup(BattleInfo const& info) {
        if(_p_battle_info == nullptr) {
            _p_battle_info = &info;
        }

        _time_line.setUp(info);
        _playable_info_ui.setUp(info);
    }
    void loadMonsterImage(std::string path)
    {
        _images_monster.emplace_back(System::Image(path));
    }

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

        // todo まとめた処理を作る
        if(_p_battle_info != nullptr && _images_monster.size() > 0) {
            auto const & enemy = _p_battle_info->enemyParty();
            auto const & members = enemy.getMembers();
            if(members.size() > 0) {
                for(int i = 0; i < _images_monster.size(); ++i) {
                    if(members[i]->isDead() == false) {
                        _images_monster[i].draw(120 + (i * 130), 150);
                    }
                }
            }
        }

        _playable_info_ui.draw();

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
    PlayableInfoUI _playable_info_ui;
    System::Image _image_bg;
    std::vector<System::Image> _images_monster;
    BattleInfo const * _p_battle_info = nullptr;
};
}}  // namespace UI::Battle