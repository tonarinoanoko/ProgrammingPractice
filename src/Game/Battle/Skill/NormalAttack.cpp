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

    std::string message = actor->name() + "の攻撃！\n" + target->name() + "に" + std::to_string(damage) + "のダメージ！";
    if(target->isDead()) {
        message += "\n" + target->name() + "を倒した！";
    }

    argument.message_manager.set(message);
}

}}  // namespace Battle::Skill
