#pragma once
#include <vector>
#include <memory>
#include "Character/Character.h"

#include "Debug/GameDebug.h"


namespace Battle {
class BattlePartyBase {
public:
    BattlePartyBase() {}

    void addMember(std::shared_ptr<Character::CharacterData> character) {
        _members.push_back(character);
    }

    std::vector<std::shared_ptr<Character::CharacterData>> const& getMembers() const {
        return _members;
    }

    std::vector<std::shared_ptr<Character::CharacterData>> & getMembers() {
        return _members;
    }

    std::shared_ptr<Character::CharacterData> const& getMember(int index) const {
        return _members[index];
    }

    std::shared_ptr<Character::CharacterData> const& getMemberFromCharacterId(int id) const {
        for(auto const & member : _members) {
            if(member->characterId() == id) {
                return member;
            }
        }

        Debug::assertLog("not member");
        return getMember(0);
    }

    // 全滅判定
    bool isAnnihilation() const {
        // 全員が死亡状態か
        for(auto const & member : _members) {
            if(member->isDead() == false) {
                return false;
            }
        }

        return true;
    }

protected:
    std::vector<std::shared_ptr<Character::CharacterData>> _members;
};
}  // Battle
