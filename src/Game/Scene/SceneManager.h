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
    static SceneManager& GetInstance() {
        static SceneManager _instance;
        return _instance;
    }

    void Update();

    void ChangeScene(EScene scene);

private:
    static SceneManager _instance;
    std::shared_ptr<SceneBase> _currentScene = nullptr;
};

}  // Scene
