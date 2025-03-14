#pragma once
#include <tuple>

namespace System {
class Rect {
public:
    // コンストラクタ
    Rect(int x = 0, int y = 0, int width = 0, int height = 0)
        : _x(x), _y(y), _w(width), _h(height) {}

    // 矩形が (px, py) を含むか判定
    bool contains(int px, int py) const {
        return (px >= _x && px < _x + _w &&
                py >= _y && py < _y + _h);
    }

    // 矩形同士の衝突判定
    bool intersects(Rect const& other) const {
        return (_x < other._x + other._w && _x + _w > other._x &&
                _y < other._y + other._h && _y + _h > other._y);
    }

    // tupleでのデータ取得
    std::tuple<int, int, int, int> getDataTuple() const
    {
        return {_x, _y, _w, _h};
    }

    int _x, _y, _w, _h;
};
}  // namespace System
