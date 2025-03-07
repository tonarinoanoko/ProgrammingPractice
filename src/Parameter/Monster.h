#pragma once
#include "ParameterBase.h"
#include "Enum/EMonsterId.h"


namespace Parameter {
namespace Monster {
class ParameterData : public ParameterBase<EMonsterId::Enum>
{
public:
    std::string _name;
    void makeParameter(EMonsterId::Enum id) override;
};

inline auto& instance() {
    return Parameters<EMonsterId::Enum, Parameter::Monster::ParameterData>::instance();
}
}}  // namespace Parameter::Monster
