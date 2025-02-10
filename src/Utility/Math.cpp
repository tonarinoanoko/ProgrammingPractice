#include "Math.h"
#include <cmath>
#include <cstdlib>


namespace Utility {
namespace Math {

int random(int value)
{
    return std::rand() % value;
}

int clamp(int value, int min, int max)
{
        return std::max(min, std::min(max, value));
}

}}  // Utility::Math
