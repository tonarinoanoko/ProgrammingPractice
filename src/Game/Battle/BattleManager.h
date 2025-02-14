#pragma once
#include "BattleInfo.h"
#include "Character/Character.h"

namespace Battle {
class BattleManager {
public:
    BattleManager() {};

    void startBattle() {}  // バトル開始
    void updateOneTrun() {}  // 1ターンの処理

private:
    BattleInfo _battle_info;
};
}  // Battle
