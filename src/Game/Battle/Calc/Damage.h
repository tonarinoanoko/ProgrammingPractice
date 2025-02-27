#pragma once
#include "Common/Value.h"
#include "Character/Character.h"


namespace Battle {
namespace Calc {

int damage(Character::CharacterData const& actor, Character::CharacterData const& target)
{
    Value damage;
    auto const& a_status = actor.status();
    auto const& t_status = target.status();
    damage.set(a_status.statusInt(EStatus::Enum::Atk) - a_status.statusInt(EStatus::Enum::Def));
    return damage.value();
}

}}  // namespace Battle::Calc
