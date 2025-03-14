#pragma once
#include "Character/Character.h"
#include "Party/PlayableParty.h"
#include "Party/EnemyParty.h"
#include "Party/BotParty.h"
#include "ActionTimeLine.h"

#include "Debug/DebugLog.h"


namespace Battle {
class BattleInfo {
public:
    BattleInfo()
    {
        _none_character = std::make_shared<Character::CharacterData>(ECharacterType::Enum::None);
    }

    PlayableParty& playerParty() { return _player_party; }
    EnemyParty& enemyParty() { return _enemy_party; }
    BotParty& botParty() { return _bot_party; }
    ActionTimeLine& actionTimeLine() { return _action_time_line; }

    PlayableParty const& playerParty() const { return _player_party; }
    EnemyParty const& enemyParty() const { return _enemy_party; }
    BotParty const& botParty() const { return _bot_party; }

    Character::CharacterData& characterData(int character_id)
    {
        // 各パーティに対してキャラクターを検索
        auto findCharacterInParty = [character_id](auto& party) -> Character::CharacterData* {
            for (auto& member : party.getMembers()) {
                if (member->characterId() == character_id) {
                    return &(*member);  // ポインタを返す
                }
            }
            return nullptr;  // キャラクターが見つからなかった場合は nullptr を返す
        };

        // プレイヤーパーティ内でキャラクターを検索
        if (auto character = findCharacterInParty(_player_party)) {
            return *character;  // 見つかったキャラクターを参照として返す
        }

        // 敵パーティ内でキャラクターを検索
        if (auto character = findCharacterInParty(_enemy_party)) {
            return *character;  // 見つかったキャラクターを参照として返す
        }

        // ボットパーティ内でキャラクターを検索
        if (auto character = findCharacterInParty(_bot_party)) {
            return *character;  // 見つかったキャラクターを参照として返す
        }

        // キャラクターが見つからない場合
        Debug::assertLog("Character not found for ID: " + std::to_string(character_id));
        return *_none_character;  // 見つからなかった場合は none_character を返す
    }


private:
    std::shared_ptr<Character::CharacterData> _none_character;
    PlayableParty _player_party;
    EnemyParty _enemy_party;
    BotParty _bot_party;
    ActionTimeLine _action_time_line;
};
}  // Battle
