#pragma once
#include <string>

namespace Common {
class MessageManager
{
public:
    MessageManager() {};
    void set(std::string const& message);
    void clear();

    std::string const& message() const { return _message; }
    bool has() const { return _message.empty() == false; }

private:
    std::string _message;
};
}  // UI
