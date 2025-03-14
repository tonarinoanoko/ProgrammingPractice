#include "MessageWindow.h"
#include "Macro/COLOR_MACRO.h"
#include "Utility/Utility.h"
#include "UI/DrawBox.h"

#include "Debug/GameDebug.h"


namespace UI {

MessageWindow::MessageWindow() 
{
    _rect = System::Rect(10, 300, 620, 170);
    _current_message.clear();
}
MessageWindow::MessageWindow(int x, int y, int width, int height)
{
    _rect = System::Rect(x, y, width, height);
    _current_message.clear();
}

void MessageWindow::setMessage(const std::string& message) {
    _current_message = std::basic_string<TCHAR>(message.begin(), message.end());

    //Debug::debugLog("set message : " + message);
}

void MessageWindow::update()
{
}

void MessageWindow::draw() const
{
    drawFrameBox(_rect);
    auto [x, y, w, h] = _rect.getDataTuple();
    if(_current_message.empty() == false) {
        DrawString(x + 10, y + 10, _current_message.c_str(), COLOR_WHITE);
    }
}

}  // UI
