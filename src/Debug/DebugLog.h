#pragma once
#include <iostream>


namespace Debug {

inline void DebugLog(const char* message) {
    std::cout << message << std::endl;
}

}  // Debug
