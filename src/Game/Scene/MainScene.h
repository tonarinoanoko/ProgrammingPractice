#pragma once
#include "DxLib.h"
#include "SceneBase.h"

namespace Scene {
class MainScene : public SceneBase {
public:
    MainScene()
    {
        setSceneId(EScene::Enum::Main);
    }

public:
    void start() override {
    }

    void update() override {
    }

    void end() override {
    }

    void draw() override {
        DrawString(100, 150, _T("Main Scene"), GetColor(255, 255, 255));
        //ScreenFlip();
    }
};
}  // Scene
