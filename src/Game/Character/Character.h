#pragma once
#include "Status.h"
#include "Common/Value.h"
#include "Enum/ECharacterType.h"
#include "Character/Skill/CharacterSkill.h"

#include "Debug/DebugLog.h"


namespace Character {

class CharacterData
{
public:
    CharacterData(ECharacterType::Enum character_type) :
    _character_type(character_type)
    {
    }

    ECharacterType::Enum characterType() const { return _character_type; }
    std::string const name() const { return _name; }
    Status const& status() const { return _status; }
    Value const& hp() const { return _now_hp; }
    std::vector<Skill::SkillData> const& skills() const { return _skills; }
    int startActionTime() const { return 100; }
    int characterId() const { return _character_id; }

    void setName(std::string name)
    {
        _name = name;
    }

    void setCharacterId(int id)
    {
        _character_id = id;
    }

    void setStatus(Status const& status)
    {
        _status = status;
        recovery();
    }

    void addSkill(Skill::SkillData const& skill_data)
    {
        _skills.emplace_back(skill_data);
    }

    void recovery()
    {
        _now_hp = _status.statusValue(EStatus::Enum::Hp);
    }

    void damage(int damage)
    {
        _now_hp.add(-damage);
    }

    void heal(int heal)
    {
        _now_hp.add(heal);
    }

    bool isDead() const
    {
        return _now_hp.value() <= 0;
    }

    void debugViewNowHp() const {
        Debug::debugLog(_name + " hp : " + _now_hp.value_str());
    }

private:
    ECharacterType::Enum _character_type;
    int _character_id;
    std::string _name;
    Value _now_hp;
    Status _status;
    std::vector<Skill::SkillData> _skills;
};

}  // Character
