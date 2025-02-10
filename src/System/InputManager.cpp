#include "InputManager.h"
#include "DxLib.h"


namespace System{
void InputManager::Update()
{
    previousKeyState = currentKeyState;  // 直前のキー状態を保存
    GetHitKeyStateAll(currentKeyState.data());  // 現在のキー状態を取得
}

bool InputManager::IsKeyDown(int keyCode) const
{
    return (currentKeyState[keyCode] && !previousKeyState[keyCode]);
}

bool InputManager::IsKeyUp(int keyCode) const
{
    return (!currentKeyState[keyCode] && previousKeyState[keyCode]);
}

bool InputManager::IsKeyPressed(int keyCode) const
{
    return (currentKeyState[keyCode]);
}

}  // System
