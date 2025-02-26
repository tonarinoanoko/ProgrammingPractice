#pragma once
#include <vector>
#include <memory>
#include "Character/Character.h"

#include "Debug/DebugLog.h"


namespace Battle {
class BattlePartyBase {
public:
    BattlePartyBase() { Debug::debugLog("BattlePartyBase()"); }

    void addMember(std::shared_ptr<Character::CharacterData> character) {
        _members.push_back(character);
    }

    std::vector<std::shared_ptr<Character::CharacterData>> const& getMembers() const {
        return _members;
    }

    std::shared_ptr<Character::CharacterData> const& getMembers(int index) const {
        return _members[index];
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
