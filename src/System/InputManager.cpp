#include "InputManager.h"
#include "DxLib.h"


namespace System{
void InputManager::Update()
{
    _previousKeyState = _currentKeyState;  // 直前のキー状態を保存
    GetHitKeyStateAll(_currentKeyState.data());  // 現在のキー状態を取得
}

bool InputManager::IsKeyDown(int keyCode) const
{
    return (_currentKeyState[keyCode] && _previousKeyState[keyCode] == false);
}

bool InputManager::IsKeyUp(int keyCode) const
{
    return (_currentKeyState[keyCode] == false && _previousKeyState[keyCode]);
}

bool InputManager::IsKeyPressed(int keyCode) const
{
    return (_currentKeyState[keyCode]);
}

}  // System
