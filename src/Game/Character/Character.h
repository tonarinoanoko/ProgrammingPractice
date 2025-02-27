#pragma once
#include "Status.h"
#include "Common/Value.h"

#include "Debug/DebugLog.h"


namespace Character {

class CharacterData
{
public:
    CharacterData() { Debug::debugLog("CharacterData()"); }
    std::string const name() const { return _name; }
    Status const& status() const { return _status; }
    Value const& hp() { return _now_hp; }
    int startActionTime() { return 100; }
    int caracterId() { return _character_id; }

    void setName(std::string name)
    {
        _name = name;
    }

    void setCharacterId(int id)
    {
        _character_id = id;
    }

    void setStatus(Status const& status)
    {
        _status = status;
        recovery();
    }

    void recovery()
    {
        _now_hp = _status.statusValue(EStatus::Enum::Hp);
        Debug::debugLog("recovery hp : " + _now_hp.value_str());
    }

    void damage(int damage)
    {
        _now_hp.add(-damage);
    }

    void heal(int heal)
    {
        _now_hp.add(heal);
    }

    bool isDead() const
    {
        return _now_hp.value() <= 0;
    }

private:
    int _character_id;
    std::string _name;
    Value _now_hp;
    Status _status;
};

}  // Character
