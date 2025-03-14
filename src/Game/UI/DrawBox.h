#pragma once
#include "DxLib.h"
#include "System/Rect.h"
#include "MACRO/COLOR_MACRO.h"


namespace UI {
// フレーム付きのBox描画
inline void drawFrameBox(System::Rect const& rect, int color_frame = COLOR_WHITE, int color_box = COLOR_BLACK)
{
    auto [x, y, w, h] = rect.getDataTuple();
    DrawBox(x, y, x + w, y + h, color_box, TRUE);
    DrawBox(x, y, x + w, y + h, color_frame, FALSE);
}
}  // namespace UI