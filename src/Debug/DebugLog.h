#pragma once
#include <iostream>


namespace Debug {

inline void debugLog(std::string message) {
    std::cout << message << std::endl;
}

inline bool assertLog(bool condition, const std::string& message = "") {
    if (condition == false) {
        std::cerr << "Assertion failed: " << message << std::endl;
        throw std::runtime_error(message);
    }

    return condition;
}

// 強制的にアサートとしてメッセージ表示
inline void assertLog(const std::string& message) {
    std::cerr << "Assertion failed: " << message << std::endl;
    throw std::runtime_error(message);
}

}  // Debug
