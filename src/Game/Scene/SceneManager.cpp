#include "SceneManager.h"
#include <string>

#include "MainScene.h"
#include "BattleScene.h"
#include "System/InputManager.h"


namespace Scene {
void SceneManager::Update()
{
    if(_current_scene == nullptr) {
        return;
    }

    _current_scene->Update();
    _current_scene->Draw();

    auto const & input = System::InputManager::GetInstance();
    if(input.IsKeyDown(KEY_INPUT_Z)) {
        ChangeScene(EScene::Battle);
    }

    if(input.IsKeyDown(KEY_INPUT_X)) {
        ChangeScene(EScene::Main);
    }
}

void SceneManager::ChangeScene(EScene scene)
{
    std::shared_ptr<SceneBase> new_scene = nullptr;
    switch(scene)
    {
        case EScene::Main:
            new_scene = std::make_shared<MainScene>();
        break;
        case EScene::Battle:
            new_scene = std::make_shared<BattleScene>();
        break;
    }

    if(new_scene) {
        _current_scene = new_scene;
    }
}

}  // Scene