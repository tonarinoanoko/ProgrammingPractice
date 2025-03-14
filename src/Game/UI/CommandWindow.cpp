#include "CommandWindow.h"
#include "DxLib.h"
#include "Macro/COLOR_MACRO.h"
#include "System/InputManager.h"
#include "Utility/Utility.h"
#include "UI/DrawBox.h"


namespace UI {
CommandWindow::CommandWindow() {}
CommandWindow::CommandWindow(int x, int y, int width, int height)
{
    _rect = System::Rect(x, y, width, height);
}

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

    drawFrameBox(_rect);
    for (size_t i = 0; i < _commands.size(); ++i) {
        int color = (i == _selected_index) ? COLOR_YELLOW : COLOR_WHITE;
        DrawString(_rect._x + 10, _rect._y + 10 + 20 * i, _commands[i].c_str(), color);
    }
}

int CommandWindow::selectedIndex() const {
    return _selected_index;
}

} // namespace UI