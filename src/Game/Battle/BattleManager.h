#pragma once
#include <string>
#include "BattleInfo.h"
#include "System/StateManager.h"
#include "Common/MessageManager.h"
#include "Character/Character.h"
#include "UI/Battle/BattleUIManager.h"

namespace Battle {
class BattleManager {
public:
    BattleManager() {};

    void startBattle(UI::Battle::BattleUIManager* ui_manager);  // バトル開始
    void update();

    bool isFinishedBattle();  // バトルが終了したか

    Common::MessageManager& messsageManager() { return _message_manager; }

private:
    enum EState
    {
        None,
        UpdateTimeLine,
        StartAction,
        SelectCommand,
        SelectTarget,
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

    System::StateManager<EState> _state = System::StateManager(EState::None);

    UI::Battle::BattleUIManager* _ui_manager = nullptr;
    EBattleCommand::Enum _pre_command = EBattleCommand::Enum::None;
    int _use_character_id = 0;

    std::vector<int> _target_character_ids;
};
}  // Battle
