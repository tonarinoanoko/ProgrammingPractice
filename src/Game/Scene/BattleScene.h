#pragma once
#include "DxLib.h"
#include "SceneBase.h"
#include "System/InputManager.h"
#include "Common/MessageManager.h"
#include "UI/MessageWindow.h"
#include "UI/CommandWindow.h"
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
        _message_window.SetMessage("Battle Scene");

        _command_window.SetCommands({"攻撃", "防御", "逃げる"});
    }

    void update() override {
        _battle_manager.updateOneTrun();

        auto & message_manager = _battle_manager.messsageManager();
        if(message_manager.has()) {
            _message_window.SetMessage(message_manager.message());
            message_manager.clear();
        }
        _message_window.Update();
        _command_window.Update();

        auto const & input = System::InputManager::instance();
        if(input.isKeyDown(KEY_INPUT_Z)) {
            _is_end = true;
        }
    }

    void end() override {
    }
    
    void draw() override {
        _message_window.Draw();
        _command_window.Draw();
    }

    bool isEnd() override {
        return _is_end;
    }

private:
    Battle::BattleManager _battle_manager;
    UI::MessageWindow _message_window;
    UI::CommandWindow _command_window;
    bool _is_end = false;
};
}  // Scene
