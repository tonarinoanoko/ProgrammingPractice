#pragma once
#include "Macro/COLOR_MACRO.h"
#include "Utility/ConvertString.h"
#include "Battle/BattleInfo.h"
using namespace Battle;  // UI::Battle内でBattleを使用しようとしたらエラーになるので仕方なくusingする


namespace UI {
namespace Battle {
class PlayableInfoUI
{
public:
    PlayableInfoUI() {}
    void setUp(BattleInfo const& info)
    {
        if(_p_party == nullptr) {
            _p_party = &info.playerParty();
        }
    }

    void draw()
    {
        if(_p_party == nullptr) {
            return;
        }

        auto const& members = _p_party->getMembers();
        for(int i = 0; i < members.size(); ++i) {
            auto const& member = members[i];

            auto name = member->name();
            auto hp = member->hp();
            DrawString(20 + (i * 120), 20, Utility::Conv::convertToStrTCHAR(name).c_str(), COLOR_WHITE);
            DrawString(20 + (i * 120), 50, Utility::Conv::convertToStrTCHAR("HP : " + hp.value_str()).c_str(), COLOR_WHITE);
        }
    }

private:
    PlayableParty const* _p_party = nullptr;
};
}}  // UI::Battle
