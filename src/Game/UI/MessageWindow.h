#pragma once
#include <string>
#include <vector>
#include "DxLib.h"
#include "System/Rect.h"


namespace UI {

class MessageWindow {
public:
    MessageWindow();
    MessageWindow(int x, int y, int width, int height);
    void setMessage(const std::string& message);
    void update();
    void draw() const;

private:
    System::Rect _rect;
    std::basic_string<TCHAR> _current_message;
};

}  // UI
