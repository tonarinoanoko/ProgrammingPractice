#include "MessageWindow.h"
#include "Macro/COLOR_MACRO.h"
#include "Utility/Utility.h"

#include "Debug/GameDebug.h"


namespace UI {

MessageWindow::MessageWindow() 
    : _x(10), _y(300), _width(620), _height(170)
    {
        _current_message.clear();
    }
MessageWindow::MessageWindow(int x, int y, int width, int height)
    : _x(x), _y(y), _width(width), _height(height)
    {
        _current_message.clear();
    }

void MessageWindow::setMessage(const std::string& message) {
    _current_message = std::basic_string<TCHAR>(message.begin(), message.end());

    Debug::debugLog("set message : " + message);
}

void MessageWindow::update()
{
}

void MessageWindow::draw() const
{
    DrawBox(_x, _y, _x + _width, _y + _height, COLOR_BLACK, TRUE);
    DrawBox(_x, _y, _x + _width, _y + _height, COLOR_WHITE, FALSE);
    if(_current_message.empty() == false) {
        DrawString(_x + 10, _y + 10, _current_message.c_str(), COLOR_WHITE);
    }
}

}  // UI
