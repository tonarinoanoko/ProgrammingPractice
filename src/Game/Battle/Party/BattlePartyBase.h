#pragma once
#include <vector>
#include <memory>
#include "Character/Character.h"


namespace Battle {
class BattlePartyBase {
public:
    void addMember(std::shared_ptr<Character::CharacterData> character) {
        _members.push_back(character);
    }

    std::vector<std::shared_ptr<Character::CharacterData>> const& getMembers() const {
        return _members;
    }

    std::shared_ptr<Character::CharacterData> const& getMembers(int index) const {
        return _members[index];
    }

protected:
    std::vector<std::shared_ptr<Character::CharacterData>> _members;
};
}  // Battle
