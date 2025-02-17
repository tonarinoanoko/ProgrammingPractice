#include "MessageWindow.h"
#include "Utility/Utility.h"

#include "Debug/DebugLog.h"


namespace UI {

MessageWindow::MessageWindow() 
    : _x(10), _y(300), _width(620), _height(170)
    {
        _messages.clear();
        _current_message.clear();
    }
MessageWindow::MessageWindow(int x, int y, int width, int height)
    : _x(x), _y(y), _width(width), _height(height)
    {
        _messages.clear();
        _current_message.clear();
    }

void MessageWindow::SetMessage(const std::string& message) {
    _messages.push_back(message);
    _finished = false;
    _char_index = 0;
    _current_message.clear();

    Debug::debugLog(_messages.front());
}

void MessageWindow::Update() {
    if (_messages.empty()) {
        return;
    }

    _frame_counter++;
    if (_frame_counter % _char_speed == 0 && _char_index < _messages.front().size()) {
        _current_message += _messages.front()[_char_index++];
    }

    if (_char_index >= _messages.front().size()) {
        _finished = true;
    }
}

void MessageWindow::Draw() {
    DrawBox(_x, _y, _x + _width, _y + _height, GetColor(0, 0, 0), TRUE);
    DrawBox(_x, _y, _x + _width, _y + _height, GetColor(255, 255, 255), FALSE);
    if(_current_message.empty() == false) {
        DrawString(_x + 10, _y + 10, _current_message.c_str(), GetColor(255, 255, 0));
    }
}

bool MessageWindow::IsFinished() const {
    return _finished;
}

}  // UI
