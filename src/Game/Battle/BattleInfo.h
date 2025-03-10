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

    std::shared_ptr<Character::CharacterData> & characterData(int character_id)
    {
        for(auto & member : _player_party.getMembers()) {
            if(member->characterId() == character_id) {
                return member;
            }
        }

        for(auto & member : _enemy_party.getMembers()) {
            if(member->characterId() == character_id) {
                return member;
            }
        }

        for(auto & member : _bot_party.getMembers()) {
            if(member->characterId() == character_id) {
                return member;
            }
        }

        Debug::assertLog("not character id");
        return _none_character;
    }

private:
    std::shared_ptr<Character::CharacterData> _none_character;
    PlayableParty _player_party;
    EnemyParty _enemy_party;
    BotParty _bot_party;
    ActionTimeLine _action_time_line;
};
}  // Battle
