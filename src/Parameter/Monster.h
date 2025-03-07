#pragma once
#include "ParameterBase.h"
#include "Enum/EMonsterId.h"
#include "Game/Character/Status.h"


namespace Parameter {
namespace Monster {
class ParameterData : public ParameterBase<EMonsterId::Enum>
{
public:
    std::string _name;
    Character::Status _status;

    void makeParameter(EMonsterId::Enum id) override;
};

inline auto& instance() {
    return Parameters<EMonsterId::Enum, Parameter::Monster::ParameterData>::instance();
}
}}  // namespace Parameter::Monster
