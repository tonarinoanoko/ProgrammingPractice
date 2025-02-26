#pragma once
#include "DxLib.h"
#include "SceneBase.h"
#include "UI/Battle/BattleUIManager.h"
#include "Battle/BattleManager.h"

#include "Debug/DebugLog.h"

namespace Scene {
class BattleScene : public SceneBase {
public:
    BattleScene();

public:
    void start() override;
    void update() override;
    void end() override;
    void draw() override;
    bool isEnd() override;

private:
    Battle::BattleManager _battle_manager;
    UI::Battle::BattleUIManager _battle_ui_manager;
    bool _is_end = false;
};
}  // Scene
