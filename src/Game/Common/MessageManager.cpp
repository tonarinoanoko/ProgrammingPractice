#include "MessageManager.h"


namespace Common {

void MessageManager::set(std::string const& message) 
{
    _message = message;
}

void MessageManager::clear()
{
    _message.clear();
}
}  // UI