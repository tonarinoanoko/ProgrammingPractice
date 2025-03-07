#pragma once
#include <array>
#include <string>
#include <unordered_map>
#include <string_view>

#include "Debug/GameDebug.h"

template <typename T>
constexpr int EnumMax() {
    return static_cast<int>(T::Max);
}

// 渡されたnameでnamespaceを定義し、Enumを作成する。Enumには末尾にNoneとMaxが追加される。
#define DEFINE_ENUM(name, ...) \
namespace name { \
enum class Enum { __VA_ARGS__, None, Max }; \
inline int max() { return EnumMax<Enum>(); } \
inline constexpr std::array<std::string_view, EnumMax<Enum>()> EnumNames = {#__VA_ARGS__}; \
\
inline const std::unordered_map<std::string_view, Enum> EnumMap = []{ \
    std::unordered_map<std::string_view, Enum> map; \
    int index = 0; \
    std::string_view names[] = {#__VA_ARGS__}; \
    for (std::string_view name : names) { \
        map[name] = static_cast<Enum>(index++); \
    } \
    return map; \
}(); \
}

// 汎用的なToString関数
template <typename T>
inline std::string_view EnumToString(T value) {
    return T::EnumNames[static_cast<int>(value)];
}

template <typename T>
inline T StringToEnum(std::string_view name) {
    auto it = T::EnumMap.find(name);
    if (it != T::EnumMap.end()) {
        return it->second;
    }

    Debug::assertLog("Invalid enum name: " + std::string(name));
    return T::None;
}