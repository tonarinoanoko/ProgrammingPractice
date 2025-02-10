#include "Math.h"
#include <cmath>
#include <cstdlib>


namespace Utility {
namespace Math {

int Random(int value)
{
    return std::rand() % value;
}

int Clamp(int value, int min, int max)
{
        return std::max(min, std::min(max, value));
}

}  // Math
}  // Utility
