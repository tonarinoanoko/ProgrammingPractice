#pragma once
#include "DxLib.h"
#include "SceneBase.h"
#include "System/InputManager.h"
#include "Battle/BattleManager.h"

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
        _battle_manager.startBattle();
    }

    void update() override {
        _battle_manager.updateOneTrun();

        auto const & input = System::InputManager::instance();
        if(input.isKeyDown(KEY_INPUT_Z)) {
            _is_end = true;
        }
    }

    void end() override {
    }
    
    void draw() override {
        DrawString(100, 150, _T("Battle Scene"), GetColor(255, 255, 255));
    }

    bool isEnd() override {
        return _is_end;
    }

private:
    Battle::BattleManager _battle_manager;
    bool _is_end = false;
};
}  // Scene
