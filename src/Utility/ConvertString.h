#pragma once
#include <string>
#include <vector>
#include <tchar.h>


namespace Utility {
namespace Conv {
std::vector<TCHAR> convertToTCHAR(const std::string& str);
}}  // Utility::Conv
