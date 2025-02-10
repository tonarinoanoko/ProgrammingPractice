#pragma once
#include <iostream>


namespace Debug {

inline void debugLog(const char* message) {
    std::cout << message << std::endl;
}

}  // Debug
