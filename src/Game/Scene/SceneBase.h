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
    virtual bool isEnd() = 0;

    EScene::Enum sceneId() const { return _scene_id; }
    EScene::Enum nextSceneId() const { return _next_scene_id; }

protected:
    void setSceneId(EScene::Enum scene_id)
    {
        _scene_id = scene_id;
    }

    void setNextSceneId(EScene::Enum scene_id)
    {
        _next_scene_id = scene_id;
    }

private:
    EScene::Enum _scene_id = EScene::Enum::None;
    EScene::Enum _next_scene_id = EScene::Enum::None;
};
}