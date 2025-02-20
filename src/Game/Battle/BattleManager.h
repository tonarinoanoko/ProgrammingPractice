#pragma once
#include <string>
#include "BattleInfo.h"
#include "Common/MessageManager.h"
#include "Character/Character.h"

namespace Battle {
class BattleManager {
public:
    BattleManager() {Debug::debugLog("BattleManager");};

    void startBattle();  // バトル開始
    void update();  // 1ターンの処理

    Common::MessageManager& messsageManager() { return _message_manager; }

private:
    enum EState
    {
        UpdateTimeLine,
        UpdateCommand,
        UpdateSkill,
        EraseTimeLine,
    };

private:
    BattleInfo _battle_info;
    ActionTimeLine _action_time_line;
    Common::MessageManager _message_manager;

    EState _state;
};
}  // Battle
