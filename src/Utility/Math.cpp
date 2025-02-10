#include "Math.h"


namespace Utility {
namespace Math {

int Clamp(int value, int min, int max) {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }

}  // Math
}  // Utility
