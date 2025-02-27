#pragma once
#include <string>
#include "BattleInfo.h"
#include "Common/MessageManager.h"
#include "Character/Character.h"
#include "UI/Battle/BattleUIManager.h"

namespace Battle {
class BattleManager {
public:
    BattleManager() { Debug::debugLog("BattleManager()"); };

    void startBattle(UI::Battle::BattleUIManager* ui_manager);  // バトル開始
    void update();  // 1ターンの処理

    bool isFinishedBattle();  // バトルが終了したか

    Common::MessageManager& messsageManager() { return _message_manager; }

private:
    enum EState
    {
        None,
        UpdateTimeLine,
        SelectCommand,
        EnemyCommand,
        UpdateSkill,
        EraseTimeLine,
    };

private:
    int makeNewCharacterId();

private:
    BattleInfo _battle_info;
    ActionTimeLine _action_time_line;
    Common::MessageManager _message_manager;

    EState _state;

    UI::Battle::BattleUIManager* _ui_manager = nullptr;
    int _pre_command = -1;
    int _use_character_id = 0;
};
}  // Battle
