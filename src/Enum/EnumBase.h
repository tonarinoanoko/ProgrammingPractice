#pragma once
#include <array>
#include <string>
#include <unordered_map>
#include <string_view>
#include <type_traits>

#include "Debug/GameDebug.h"

// Enumの最大値を返す関数
template <typename T>
constexpr int EnumMax() {
    return static_cast<int>(T::Max);
}

// Enumを作成するマクロ
#define DEFINE_ENUM(name, ...) \
namespace name { \
    enum class Enum { __VA_ARGS__, None, Max }; \
    inline int max() { return EnumMax<Enum>(); } \
    /* EnumNamesとEnumMapを名前空間内に定義 */ \
    inline constexpr std::array<std::string_view, static_cast<int>(Enum::Max)> EnumNames = {#__VA_ARGS__, "None"}; \
    \
    inline const std::unordered_map<std::string_view, Enum> EnumMap = []{ \
        std::unordered_map<std::string_view, Enum> map; \
        int index = 0; \
        std::string_view names[] = {#__VA_ARGS__, "None"}; \
        for (std::string_view name : names) { \
            map[name] = static_cast<Enum>(index++); \
        } \
        return map; \
    }(); \
    inline std::string_view EnumToString(Enum value) {\
        return EnumNames[static_cast<int>(value)];\
    }\
    inline Enum StringToEnum(std::string_view str) {\
        auto it = EnumMap.find(str);\
        if (it != EnumMap.end()) {\
            return it->second;\
        }\
        Debug::assertLog("Invalid enum name: " + std::string(str));\
        return Enum::None;\
    }\
}
