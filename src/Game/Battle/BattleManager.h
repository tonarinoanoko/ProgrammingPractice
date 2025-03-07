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
    enum class EState
    {
        None,
        UpdateTimeLine,
        StartAction,
        SelectCommand,
        SelectSkill,
        SelectTarget,
        EnemyCommand,
        UpdateSkill,
        EndTimeLine,
        FinishedBattle,
    };

private:
    int makeNewCharacterId();
    bool isNextFinishedBattle();

private:
    void UpdateTimeLine();
    void StartAction();
    void SelectCommand();
    void SelectSkill();
    void SelectTarget();
    void EnemyCommand();
    void UpdateSkill();
    void EndTimeLine();

private:
    BattleInfo _battle_info;
    Common::MessageManager _message_manager;

    System::StateManager<EState> _state = System::StateManager(EState::None);

    UI::Battle::BattleUIManager* _ui_manager = nullptr;
    EBattleCommand::Enum _pre_command = EBattleCommand::Enum::None;
    int _use_character_id = 0;

    ESkillId::Enum _use_skill;
    std::vector<int> _target_character_ids;
    int _next_action_time = 0;
};
}  // Battle
