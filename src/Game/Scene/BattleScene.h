#pragma once
#include "DxLib.h"
#include "SceneBase.h"
#include "System/InputManager.h"
#include "UI/MessageWindow.h"
#include "Battle/BattleManager.h"

#include "Debug/DebugLog.h"

namespace Scene {
class BattleScene : public SceneBase {
public:
    BattleScene()
    {
        setSceneId(EScene::Enum::Battle);
        setNextSceneId(EScene::Enum::Main);
    }

public:
    void start() override {
        Debug::debugLog("Start Battle Scene");
        _battle_manager.startBattle();
    }

    void update() override {
        _battle_manager.updateOneTrun();
        _message_window.Update();

        auto const & input = System::InputManager::instance();
        if(input.isKeyDown(KEY_INPUT_Z)) {
            _is_end = true;
        }
    }

    void end() override {
    }
    
    void draw() override {
        _message_window.Draw();
    }

    bool isEnd() override {
        return _is_end;
    }

private:
    Battle::BattleManager _battle_manager;
    UI::MessageWindow _message_window;
    bool _is_end = false;
};
}  // Scene
