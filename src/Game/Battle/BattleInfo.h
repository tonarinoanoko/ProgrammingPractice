#pragma once
#include "Character/Character.h"
#include "PlayableParty.h"
#include "EnemyParty.h"


class BattleInfo {
private:
    PlayableParty _playerParty;
    EnemyParty _enemyParty;
    int _turnCount = 0;  // バトルのターン数
    std::vector<std::shared_ptr<Character::CharacterData>> _actionOrder; // 行動順リスト

public:
    BattleInfo(const PlayableParty& player, const EnemyParty& enemy);

    void NextTurn();  // ターンを進める
    bool IsBattleOver() const;  // 勝敗判定
    const std::vector<std::shared_ptr<Character::CharacterData>>& GetActionOrder() const;
    
    PlayableParty& GetPlayerParty();
    EnemyParty& GetEnemyParty();
};
