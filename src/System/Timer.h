#pragma once
#include "DxLib.h"

namespace System {
class Timer {
public:
    // コンストラクタ（開始時間を0に設定）
    Timer() : _start_time(0) {}

    // タイマー開始
    void start()
    {
        _start_time = GetNowCount();
    }

    // 経過時間を取得（ミリ秒単位）
    int elapsed() const
    {
        return GetNowCount() - _start_time;
    }

    // 指定時間が経過したか判定
    bool isTimeUp(int ms) const
    {
        return elapsed() >= ms;
    }

private:
    int _start_time = 0; // 開始時間
};
}  // namespace System
