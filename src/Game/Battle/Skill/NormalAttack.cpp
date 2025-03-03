#include "NormalAttack.h"
#include "Battle/Calc/Damage.h"


namespace Battle {
namespace Skill {

void NormalAttack::execute(Argument& argument)
{
    auto damage = Calc::damage(argument.actor, argument.target);
    argument.target.damage(damage);

    argument.message_manager.set(argument.actor.name() + "の攻撃！\n" + argument.target.name() + "に" + std::to_string(damage) + "のダメージ！");
}

}}  // namespace Battle::Skill
