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
    void updateOneTrun() {}  // 1ターンの処理

    Common::MessageManager& messsageManager() { return _message_manager; }

private:
    BattleInfo _battle_info;
    Common::MessageManager _message_manager;
};
}  // Battle
