#pragma once
#include "Macro/COLOR_MACRO.h"
#include "Utility/ConvertString.h"
#include "Battle/BattleInfo.h"
using namespace Battle;  // UI::Battle内でBattleを使用しようとしたらエラーになるので仕方なくusingする


namespace UI {
namespace Battle {
class ActionTimeLineUI
{
public:
    ActionTimeLineUI() {};
    void setUp(BattleInfo & info)
    {
        auto & time_line = info.actionTimeLine();
        if(_p_battle_time_line == nullptr) {
            _p_battle_time_line = &time_line;
        }
    }

    void draw() {
        if(_p_battle_time_line == nullptr) {
            return;
        }

        auto const& entrys = _p_battle_time_line->actionEntrys();
        for(int i = 0; i < entrys.size(); ++i) {
            auto const& entry = entrys[i];
            std::string disp = Utility::Conv::padWithSpaces(entry._action_time, 3) + "("+ Utility::Conv::padWithSpaces(entry._cool_time, 3) + ") : " + entry._name;
            DrawString(450, 30 + 20 * i, Utility::Conv::convertToStrTCHAR(disp).c_str(), COLOR_WHITE);
        }
    };

private:
    ActionTimeLine const* _p_battle_time_line = nullptr;
};

}}  // namespace UI::Battle
