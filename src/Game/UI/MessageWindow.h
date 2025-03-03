#pragma once
#include <string>
#include <vector>
#include <deque>
#include <memory>
#include "DxLib.h"


namespace UI {

class MessageWindow {
public:
    MessageWindow();
    MessageWindow(int x, int y, int width, int height);
    void setMessage(const std::string& message);
    void update();
    void draw() const;

private:
    int _x, _y, _width, _height;
    std::basic_string<TCHAR> _current_message;
};

}  // UI
