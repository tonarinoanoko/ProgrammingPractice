#pragma once

#include "magic_enum/magic_enum.hpp"

#define DEFINE_ENUM(name, ...) \
namespace name {\
enum class Enum { __VA_ARGS__, None, Max }; \
}

template <typename T>
int EnumMax()
{
    return static_cast<int>(T::Max);
}

template <typename T>
std::string_view EnumToString(T id)
{
    return magic_enum::enum_name(id);
}

template <typename T>
T StringToEnum(std::string str)
{
    return magic_enum::enum_cast<T>(str);
}
