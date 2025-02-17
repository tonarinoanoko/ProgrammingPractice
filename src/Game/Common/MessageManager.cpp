#include "MessageManager.h"


namespace Common {

void MessageManager::set(std::string const& message) 
{
    _current_message = message;
}

void MessageManager::clear()
{
    _current_message.clear();
}
}  // UI