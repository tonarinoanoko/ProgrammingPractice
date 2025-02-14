#pragma pnce
#include <vector>
#include <memory>
#include "Character/Character.h"


class BattlePartyBase {
protected:
    std::vector<std::shared_ptr<Character::CharacterData>> _members;

public:
    void AddMember(std::shared_ptr<Character::CharacterData> character) {
        _members.push_back(character);
    }

    const std::vector<std::shared_ptr<Character::CharacterData>>& GetMembers() const {
        return _members;
    }
};
