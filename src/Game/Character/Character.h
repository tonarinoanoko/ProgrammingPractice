#pragma once
#include "Status.h"
#include "Common/Value.h"


namespace Character {

class CharacterData
{
public:
    Status const& status() const { return _status; }

    Value& hp() { return _now_hp; }

private:
    Value _now_hp;
    Status _status;
};

}  // Character
