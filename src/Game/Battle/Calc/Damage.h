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
    float def_par = static_cast<float>(a_atk) / static_cast<float>(t_def);  // 防御力に対する攻撃力の比率を浮動小数点で計算
    def_par = std::min(3.0f, def_par);
    float rand_factor = 1.0f + (Utility::Math::random(101) / 100.0f);  // ランダム係数(1.0～2.0)
    float damage = a_atk * rand_factor * def_par;  // ダメージ計算
    int final_damage = static_cast<int>(ceil(damage));  // ダメージの切り上げ
    damage_val.set(final_damage);
    return damage_val.value();
}

}}  // namespace Battle::Calc
