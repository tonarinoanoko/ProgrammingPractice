#include "SceneManager.h"
#include <string>

#include "MainScene.h"
#include "BattleScene.h"
#include "System/InputManager.h"


namespace Scene {
void SceneManager::update()
{
    if(_current_scene == nullptr) {
        return;
    }

    _current_scene->update();
    _current_scene->draw();

    auto const & input = System::InputManager::getInstance();
    if(input.isKeyDown(KEY_INPUT_Z)) {
        changeScene(EScene::Enum::Battle);
    }

    if(input.isKeyDown(KEY_INPUT_X)) {
        changeScene(EScene::Enum::Main);
    }
}

void SceneManager::changeScene(EScene::Enum scene)
{
    std::shared_ptr<SceneBase> new_scene = nullptr;
    switch(scene)
    {
        case EScene::Enum::Main:
            new_scene = std::make_shared<MainScene>();
        break;
        case EScene::Enum::Battle:
            new_scene = std::make_shared<BattleScene>();
        break;
    }

    if(new_scene) {
        _current_scene = new_scene;
    }
}

}  // Scene