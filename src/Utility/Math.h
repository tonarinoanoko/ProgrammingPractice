#pragma once


namespace Utility {
namespace Math {

/// 0 ～ value - 1までの乱数の生成
int random(int value);

/// valueをmin/maxで丸める
int clamp(int value, int min, int max);

}}  // Utility::Math
