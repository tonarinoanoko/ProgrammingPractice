#include "Enemy.h"


namespace Character {

std::shared_ptr<Character::EnemyData> makeEnemy(EMonsterId::Enum id)
{
    auto enemy = std::make_shared<Character::EnemyData>();
    auto enemy_param = Parameter::Monster::instance();
    auto enemy_data = enemy_param.parameter(id);
    enemy->setName(enemy_data._name);
    enemy->setStatus(enemy_data._status);
    enemy->debugViewNowHp();
    return enemy;
}

}  // namespace Character
