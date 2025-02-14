#include "ConvertString.h"
#include <windows.h>


namespace Utility {
namespace Conv {

std::vector<TCHAR> convertToTCHAR(const std::string& str)
{
    int size_needed = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
    std::vector<TCHAR> tstr(size_needed);  // TCHARはwchar_tとして扱われる
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, reinterpret_cast<wchar_t*>(tstr.data()), size_needed);
    return tstr;
}

}}  // Utility::Conv
