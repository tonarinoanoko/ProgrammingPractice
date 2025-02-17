#pragma once
#include <vector>
#include <string>
#include "DxLib.h"


namespace UI {

class CommandWindow {
public:
    CommandWindow();
    CommandWindow(int x, int y, int width, int height);

    void SetCommands(const std::vector<std::string>& commands);
    void Update();
    void Draw() const;
    int GetSelectedCommand() const;

private:
    int _x, _y, _width, _height;
    std::vector<std::basic_string<TCHAR>> _commands;
    int _selected_index = 0;
};

} // namespace UI
