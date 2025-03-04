#include "SkillHeal1.h"
#include "Battle/Calc/Damage.h"


namespace Battle {
namespace Skill {

void SkillHeal1::execute(Argument& argument)
{
    auto const & actor = argument._battle_info.characterData(argument.actor);
    auto & target = argument._battle_info.characterData(argument.targets[0]);
    target->heal(100);

    argument.message_manager.set(actor->name() + "のスキル回復！\n" + target->name() + "は" + std::to_string(100) + "の回復");
}

}}  // namespace Battle::Skill
