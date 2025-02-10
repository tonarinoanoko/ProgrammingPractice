#pragma once

namespace Scene {
class SceneBase {
public:
    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void End() = 0;
    virtual void Draw() = 0;
    virtual ~SceneBase() = default;
};
}