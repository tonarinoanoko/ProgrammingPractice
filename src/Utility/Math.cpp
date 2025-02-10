#include "Math.h"
#include <cmath>


namespace Utility {
namespace Math {

int Clamp(int value, int min, int max) {
        return std::max(min, std::min(max, value));
    }

}  // Math
}  // Utility
