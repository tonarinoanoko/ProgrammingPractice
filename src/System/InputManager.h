#pragma once
#include <array>


namespace System {
class InputManager
{
private:
    InputManager() {}

public:
    static InputManager& GetInstance() {
        static InputManager _instance;
        return _instance;
    }

    void Update();

    // キーが押された瞬間
    bool IsKeyDown(int key_code) const;
    // キーが離された瞬間
    bool IsKeyUp(int key_code) const;
    // キーが押され続けている
    bool IsKeyPressed(int key_code) const;

private:
    static InputManager _instance;
    std::array<char, 256> _current_key_state{};
    std::array<char, 256> _prev_key_state{};
};

}  // System
