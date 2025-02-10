#pragma once
#include "DxLib.h"
#include "SceneBase.h"

namespace Scene {
class BattleScene : public SceneBase {
public:
    void Start() override {
    }

    void Update() override {
    }

    void End() override {
    }
    
    void Draw() override {
        DrawString(100, 150, _T("Battle Scene"), GetColor(255, 255, 255));
        //ScreenFlip();
    }
};
}  // Scene
