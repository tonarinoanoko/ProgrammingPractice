#pragma once
#include <string>
#include <vector>
#include <windows.h>


namespace Utility {
namespace Conv {
std::vector<TCHAR> convertToTCHAR(const std::string& str) {
    int size_needed = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
    std::vector<TCHAR> wstr(size_needed);
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wstr.data(), size_needed);
    return wstr;
}
}}  // Utility::Conv
