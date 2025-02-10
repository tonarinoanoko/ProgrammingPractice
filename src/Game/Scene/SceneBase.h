#pragma once
#include "Enum/EScene.h"


namespace Scene {
class SceneBase {
public:
    virtual ~SceneBase() = default;
    virtual void start() = 0;
    virtual void update() = 0;
    virtual void end() = 0;
    virtual void draw() = 0;

    EScene::Enum sceneId() { return _scene_id; }

protected:
    void setSceneId(EScene::Enum scene_id)
    {
        _scene_id = scene_id;
    }

private:
    EScene::Enum _scene_id = EScene::Enum::None;
};
}