#pragma once
#include <vector>
#include <string>


namespace UI {

class CommandWindow {
public:
    CommandWindow(int x, int y, int width, int height);

    void SetCommands(const std::vector<std::string>& commands);
    void Update();
    void Draw() const;
    int GetSelectedCommand() const;

private:
    int _x, _y, _width, _height;
    std::vector<std::string> _commands;
    int _selectedIndex = 0;
};

} // namespace UI
