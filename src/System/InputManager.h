#pragma once
#include <array>


namespace System {
class InputManager
{
private:
    InputManager() {}

public:
    static InputManager& GetInstance() {
        static InputManager instance;
        return instance;
    }

    void Update();

    // キーが押された瞬間
    bool IsKeyDown(int keyCode) const;
    // キーが離された瞬間
    bool IsKeyUp(int keyCode) const;
    // キーが押され続けている
    bool IsKeyPressed(int keyCode) const;

private:
    static InputManager instance;
    std::array<char, 256> currentKeyState{};
    std::array<char, 256> previousKeyState{};
};

}  // System
