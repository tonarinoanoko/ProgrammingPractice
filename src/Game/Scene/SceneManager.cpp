#include "SceneManager.h"
#include <string>

#include "MainScene.h"
#include "BattleScene.h"


namespace Scene {
void SceneManager::update()
{
    if(_current_scene == nullptr) {
        return;
    }

    _current_scene->update();
    _current_scene->draw();

    if(_current_scene->isEnd()) {
        changeScene(_current_scene->nextSceneId());
    }
}

void SceneManager::changeScene(EScene::Enum scene)
{
    if(_current_scene && _current_scene->sceneId() == scene) {
        return;
    }
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