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
        static SceneManager instance;
        return instance;
    }

    void Update();

    void ChangeScene(EScene scene);

private:
    static SceneManager instance;
    std::shared_ptr<SceneBase> currentScene = nullptr;
};

}  // Scene
