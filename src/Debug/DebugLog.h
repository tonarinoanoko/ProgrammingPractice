#pragma once
#include <iostream>


namespace Debug {

inline void debugLog(std::string message) {
    std::cout << message << std::endl;
}

}  // Debug
