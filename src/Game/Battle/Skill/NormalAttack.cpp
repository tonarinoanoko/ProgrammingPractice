#include "NormalAttack.h"
#include "Battle/Calc/Damage.h"


namespace Battle {
namespace Skill {

void NormalAttack::execute(Argument& argument)
{
    auto const & actor = argument._battle_info.characterData(argument.actor);
    auto & target = argument._battle_info.characterData(argument.targets[0]);
    auto damage = Calc::damage(*actor, *target);
    target->damage(damage);

    argument.message_manager.set(actor->name() + "の攻撃！\n" + target->name() + "に" + std::to_string(damage) + "のダメージ！");
}

}}  // namespace Battle::Skill
