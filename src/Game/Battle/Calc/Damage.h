#pragma once
#include <math.h>
#include "Utility/Utility.h"
#include "Common/Value.h"
#include "Character/Character.h"


namespace Battle {
namespace Calc {

inline int damage(Character::CharacterData const& actor, Character::CharacterData const& target)
{
    Value damage_val;
    int a_atk = actor.status().statusInt(EStatus::Enum::Atk);
    int t_def = std::max(1, target.status().statusInt(EStatus::Enum::Def));
    float def_par = a_atk / t_def;
    float rand = 1.0 + (Utility::Math::random(101) / 100.0f);
    int damage = ceil(static_cast<float>(a_atk) * rand * def_par);
    damage_val.set(damage);
    return damage_val.value();
}

}}  // namespace Battle::Calc
