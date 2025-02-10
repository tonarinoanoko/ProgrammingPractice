#pragma once
#include "DxLib.h"
#include "SceneBase.h"

namespace Scene {
class MainScene : public SceneBase {
public:
    void Start() override {
    }

    void Update() override {
    }

    void End() override {
    }

    void Draw() override {
        DrawString(100, 150, _T("Main Scene"), GetColor(255, 255, 255));
        //ScreenFlip();
    }
};
}  // Scene
