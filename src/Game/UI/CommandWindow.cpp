#include "CommandWindow.h"
#include "DxLib.h"
#include "Utility/Utility.h"


namespace UI {
CommandWindow::CommandWindow(int x, int y, int width, int height)
    : _x(x), _y(y), _width(width), _height(height) {}

void CommandWindow::SetCommands(const std::vector<std::string>& commands) {
    _commands = commands;
    _selectedIndex = 0;
}

void CommandWindow::Update() {
    if (CheckHitKey(KEY_INPUT_UP)) {
        _selectedIndex = (_selectedIndex - 1 + _commands.size()) % _commands.size();
    }
    if (CheckHitKey(KEY_INPUT_DOWN)) {
        _selectedIndex = (_selectedIndex + 1) % _commands.size();
    }
}

void CommandWindow::Draw() const {
    for (size_t i = 0; i < _commands.size(); ++i) {
        int color = (i == _selectedIndex) ? GetColor(255, 255, 0) : GetColor(255, 255, 255);
        auto message = Utility::Conv::convertToTCHAR(_commands[i]);
        DrawString(_x, _y + 20 * i, message.data(), color);
    }
}

int CommandWindow::GetSelectedCommand() const {
    return _selectedIndex;
}

} // namespace UI