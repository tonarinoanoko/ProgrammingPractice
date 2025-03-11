#pragma once
#include <string>
#include <vector>
#include <tchar.h>


namespace Utility {
namespace Conv {
std::vector<TCHAR> convertToTCHAR(const std::string& str);
std::basic_string<TCHAR> convertToStrTCHAR(const std::string& str);

// 渡した数字を空白桁を追加したstringで返す
std::string padWithSpaces(int num, int width);

}}  // Utility::Conv
