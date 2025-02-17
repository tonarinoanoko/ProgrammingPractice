#include "ConvertString.h"
#include <windows.h>

#include "Debug/DebugLog.h"


namespace Utility {
namespace Conv {

std::vector<TCHAR> convertToTCHAR(const std::string& str)
{
    int size_needed = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
    std::vector<TCHAR> tstr(size_needed);  // TCHARはwchar_tとして扱われる
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, reinterpret_cast<wchar_t*>(tstr.data()), size_needed);
    return tstr;
}

std::basic_string<TCHAR> convertToStrTCHAR(const std::string& str) {
#ifdef UNICODE
    int size_needed = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
    if (size_needed <= 0) return std::basic_string<TCHAR>();

    std::vector<wchar_t> buffer(size_needed);
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, buffer.data(), size_needed);

    return std::basic_string<TCHAR>(buffer.begin(), buffer.end() - 1); // -1 で末尾の `\0` を除外
#else
    return str;
#endif
}

}}  // Utility::Conv
