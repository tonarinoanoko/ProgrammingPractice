#pragma once


namespace Utility {
namespace Math {

/// 0 ～ value - 1までの乱数の生成
int Random(int value);

/// valueをmin/maxで丸める
int Clamp(int value, int min, int max);

}  // Math
}  // Utility
