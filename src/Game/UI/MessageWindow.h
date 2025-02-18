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
    void draw();
    bool finished() const;
    
private:
    int const _char_speed = 2; // 文字が表示されるフレーム間隔

private:
    int _x, _y, _width, _height;
    std::deque<std::string> _messages;
    std::basic_string<TCHAR> _current_message;
    size_t _char_index = 0;
    bool _finished = false;
    int _frame_counter = 0;
};

}  // UI
