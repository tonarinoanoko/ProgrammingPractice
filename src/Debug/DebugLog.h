#pragma once
#include <iostream>


namespace Debug {

inline void debugLog(std::string message) {
    std::cout << message << std::endl;
}

inline void assertLog(bool condition, const std::string& message = "") {
    if (condition == false) {
        std::cerr << "Assertion failed: " << message << std::endl;
        throw std::runtime_error(message);
    }
}

}  // Debug
