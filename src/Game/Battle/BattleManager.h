#pragma once
#include "BattleInfo.h"
#include "Character/Character.h"

class BattleManager {
private:
    BattleInfo _battleInfo;

public:
    BattleManager(const PlayableParty& player, const EnemyParty& enemy);
    
    void StartBattle();  // バトル開始
    void Update();  // 1ターンの処理
    void ExecuteAction(std::shared_ptr<Character::CharacterData> actor);  // キャラの行動を処理
};
