#pragma once
#include "DxLib.h"
#include "SceneBase.h"

namespace Scene {
class BattleScene : public SceneBase {
public:
    BattleScene()
    {
        setSceneId(EScene::Enum::Battle);
    }

public:
    void start() override {
    }

    void update() override {
    }

    void end() override {
    }
    
    void draw() override {
        DrawString(100, 150, _T("Battle Scene"), GetColor(255, 255, 255));
        //ScreenFlip();
    }
};
}  // Scene
