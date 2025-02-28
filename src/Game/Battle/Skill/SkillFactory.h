#pragma once
#include <memory>
#include <map>
#include <functional>
#include "SkillBase.h"
#include "Enum/ESkillType.h"

#include "NormalAttack.h"

#include "Debug/DebugLog.h"


namespace Battle {
namespace Skill {

class SkillFactory {
public:
    static SkillFactory& instance() {
        static SkillFactory factory;
        return factory;
    }

    void registerSkill(ESkillType::Enum skillType, std::function<std::unique_ptr<SkillBase>()> creator) {
        _skill_map[skillType] = creator;
    }

    std::unique_ptr<SkillBase> create(ESkillType::Enum skill) {
        auto it = _skill_map.find(skill);
        if (it != _skill_map.end()) {
            return it->second();
        }
        Debug::assertLog("Unknown skill type.");
        return nullptr;
    }

private:
    SkillFactory()
    {
        registerSkill(ESkillType::Enum::NormalAttack, []() { return std::make_unique<NormalAttack>(); });
    }

private:
    std::map<ESkillType::Enum, std::function<std::unique_ptr<SkillBase>()>> _skill_map;
};

}}  // namespace Battle::Skill
