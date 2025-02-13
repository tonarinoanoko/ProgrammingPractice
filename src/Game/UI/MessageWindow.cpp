#include "MessageWindow.h"
#include "Utility/Utility.h"


namespace UI {

MessageWindow::MessageWindow(int x, int y, int width, int height)
    : _x(x), _y(y), _width(width), _height(height) {}

void MessageWindow::SetMessage(const std::string& message) {
    _messages.push_back(message);
    _finished = false;
    _char_index = 0;
    _current_message.clear();
}

void MessageWindow::Update() {
    if (_messages.empty()) return;

    _frame_counter++;
    if (_frame_counter % _char_speed == 0 && _char_index < _messages.front().size()) {
        _current_message += _messages.front()[_char_index++];
    }

    if (_char_index >= _messages.front().size()) {
        _finished = true;
    }
}

void MessageWindow::Draw() const {
    DrawBox(_x, _y, _x + _width, _y + _height, GetColor(0, 0, 0), TRUE);
    auto message = Utility::Conv::convertToTCHAR(_current_message);
    DrawString(_x + 10, _y + 10, message.data(), GetColor(255, 255, 255));
}

bool MessageWindow::IsFinished() const {
    return _finished;
}

}  // UI
