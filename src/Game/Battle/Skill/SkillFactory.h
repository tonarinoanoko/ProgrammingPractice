#pragma once
#include <memory>
#include <map>
#include <functional>
#include "SkillBase.h"
#include "Enum/ESkillType.h"

// スキルを追加したらヘッダーを以下に追加
#include "NormalAttack.h"
#include "SkillAttack1.h"
#include "SkillHeal1.h"

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
        // スキルを追加したら以下でスキルを登録
        registerSkill(ESkillType::Enum::NormalAttack, []() { return std::make_unique<NormalAttack>(); });
        registerSkill(ESkillType::Enum::SkillAttack1, []() { return std::make_unique<SkillAttack1>(); });
        registerSkill(ESkillType::Enum::SkillHeal1, []() { return std::make_unique<SkillHeal1>(); });
    }

private:
    std::map<ESkillType::Enum, std::function<std::unique_ptr<SkillBase>()>> _skill_map;
};

}}  // namespace Battle::Skill
