#pragma once
#include <memory>
#include "SceneBase.h"


namespace Scene {

class SceneManager
{
private:
    SceneManager() {}

public:
    enum EScene
    {
        Main,
        Battle
    };

public:
    static SceneManager& getInstance() {
        static SceneManager _instance;
        return _instance;
    }

    void update();

    void changeScene(EScene scene);

private:
    static SceneManager _instance;
    std::shared_ptr<SceneBase> _current_scene = nullptr;
};

}  // Scene
