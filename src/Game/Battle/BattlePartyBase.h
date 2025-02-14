#pragma once
#include <vector>
#include <memory>
#include "Character/Character.h"


namespace Battle {
class BattlePartyBase {
public:
    void AddMember(std::shared_ptr<Character::CharacterData> character) {
        _members.push_back(character);
    }

    const std::vector<std::shared_ptr<Character::CharacterData>>& GetMembers() const {
        return _members;
    }

protected:
    std::vector<std::shared_ptr<Character::CharacterData>> _members;
};
}  // Battle
