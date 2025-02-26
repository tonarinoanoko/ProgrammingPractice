#include "CommandWindow.h"
#include "DxLib.h"
#include "System/InputManager.h"
#include "Utility/Utility.h"


namespace UI {
CommandWindow::CommandWindow()
    : _x(10), _y(200), _width(100), _height(100) {}
CommandWindow::CommandWindow(int x, int y, int width, int height)
    : _x(x), _y(y), _width(width), _height(height) {}

void CommandWindow::setDrawingComand(bool draw)
{
    _draw_command = draw;
}

void CommandWindow::setCommands(const std::vector<std::string>& commands) {
    _commands.clear();
    for(auto const& comand : commands) {
        _commands.emplace_back(Utility::Conv::convertToStrTCHAR(comand));
    }
    _selected_index = 0;
}

void CommandWindow::update() {
    if(_draw_command == false) {
        return;
    }

    auto const& input_manager = System::InputManager::instance();
    if (input_manager.isKeyDown(KEY_INPUT_UP)) {
        _selected_index = (_selected_index - 1 + _commands.size()) % _commands.size();
    }
    if (input_manager.isKeyDown(KEY_INPUT_DOWN)) {
        _selected_index = (_selected_index + 1) % _commands.size();
    }
}

void CommandWindow::draw() const {
    if(_draw_command == false) {
        return;
    }

    for (size_t i = 0; i < _commands.size(); ++i) {
        int color = (i == _selected_index) ? GetColor(255, 255, 0) : GetColor(255, 255, 255);
        DrawString(_x, _y + 20 * i, _commands[i].c_str(), color);
    }
}

int CommandWindow::selectedCommand() const {
    return _selected_index;
}

} // namespace UI