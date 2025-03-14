#include "ConvertString.h"
#include <windows.h>


namespace Utility {
namespace Conv {

std::basic_string<TCHAR> convertToStrTCHAR(const std::string& str) {
#ifdef UNICODE
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
    if (size_needed <= 0) return std::basic_string<TCHAR>();

    std::wstring wstr(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], size_needed);

    return std::basic_string<TCHAR>(wstr);
#else
    return str;
#endif
}

std::string padWithSpaces(int num, int width) {
    std::string str = std::to_string(num);
    int padding = width - str.length();
    
    // 必要な空白を先頭に追加
    if (padding > 0) {
        str = std::string(padding, ' ') + str;
    }

    return str;
}

}}  // Utility::Conv
