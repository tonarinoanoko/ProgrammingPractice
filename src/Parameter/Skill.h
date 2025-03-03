#pragma once
#include <map>
#include "Enum/ESkillId.h"
#include "Enum/ESkillType.h"

#include "Debug/DebugLog.h"


namespace Parameter {
namespace Skill {

struct ParameterData
{
public:
    ESkillType::Enum _skill_type;
};

// todo 現在は即値だけれど外にパラメーターを用意して対応したいね
ParameterData makeParameterData(ESkillId::Enum id)
{
    switch(id)
    {
        case ESkillId::Enum::NormalAttack:
            return { ESkillType::Enum::NormalAttack };
        break;

        default:
        Debug::assertLog("not use id");
        break;
    }
}

class Parameter
{
public:
    Parameter(ParameterData data) :
    _data(data)
    {
    }

    ESkillType::Enum skillType() const { return _data._skill_type; }

private:
    ParameterData _data;
};

class Parameters
{
public:
    Parameters()
    {
        for(int i = 0; i < ESkillId::max(); ++i) {
            auto id = static_cast<ESkillId::Enum>(i);
            if(id == ESkillId::Enum::None || id == ESkillId::Enum::Max) {
                continue;
            }

            _param_map[id] = Parameter(makeParameterData(id));
        }
    }

    static Parameters& instance() {
        static Parameters _instance;
        return _instance;
    }

    Parameter const& parameter(ESkillId::Enum id) const {
        auto it = _param_map.find(id);
        if (it == _param_map.end()) {
            Debug::assertLog("Skill ID not found!");
            static Parameter default_parameter({ ESkillType::Enum::NormalAttack });
            return default_parameter;
        }
        return it->second;
    }

private:
    static Parameters _instance;
    std::map<ESkillId::Enum, Parameter> _param_map;
};

}}  // namespace Parameter::Skill
