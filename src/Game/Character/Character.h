#pragma once
#include "Status.h"
#include "Common/Value.h"


namespace Character {

class CharacterData
{
public:
    Status const& status() const { return _status; }
    Value const& hp() { return _now_hp; }

    void setStatus(Status const& status)
    {
        _status = status;
        recovery();
    }

    void recovery()
    {
        _now_hp = _status.statusValue(EStatus::Enum::Hp);
    }

    void damage(int damage)
    {
        _now_hp.add(-damage);
    }

    bool isDead()
    {
        return _now_hp.value() == 0;
    }

private:
    Value _now_hp;
    Status _status;
};

}  // Character
