#pragma once
#include "DxLib.h"
#include "SceneBase.h"
#include "System/InputManager.h"

namespace Scene {
class MainScene : public SceneBase {
public:
    MainScene()
    {
        setSceneId(EScene::Enum::Main);
        setNextSceneId(EScene::Enum::Battle);
    }

public:
    void start() override {
    }

    void update() override {
        auto const & input = System::InputManager::instance();
        if(input.isKeyDown(KEY_INPUT_Z)) {
            _is_end = true;
        }
    }

    void end() override {
    }

    void draw() override {
        DrawString(100, 150, _T("Main Scene"), GetColor(255, 255, 255));
    }

    bool isEnd() override {
        return _is_end;
    }

private:
    bool _is_end = false;
};
}  // Scene
