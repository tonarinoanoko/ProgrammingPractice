#include "InputManager.h"
#include "DxLib.h"


namespace System{
void InputManager::update()
{
    _prev_key_state = _current_key_state;  // 直前のキー状態を保存
    GetHitKeyStateAll(_current_key_state.data());  // 現在のキー状態を取得
}

bool InputManager::isKeyDown(int key_code) const
{
    return (_current_key_state[key_code] && _prev_key_state[key_code] == false);
}

bool InputManager::isKeyUp(int key_code) const
{
    return (_current_key_state[key_code] == false && _prev_key_state[key_code]);
}

bool InputManager::isKeyPressed(int key_code) const
{
    return (_current_key_state[key_code]);
}

}  // System
