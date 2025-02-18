#pragma once
#include <vector>
#include <string>
#include "DxLib.h"


namespace UI {

class CommandWindow {
public:
    CommandWindow();
    CommandWindow(int x, int y, int width, int height);

    void setCommands(const std::vector<std::string>& commands);
    void update();
    void draw() const;
    int selectedCommand() const;

private:
    int _x, _y, _width, _height;
    std::vector<std::basic_string<TCHAR>> _commands;
    int _selected_index = 0;
};

} // namespace UI
