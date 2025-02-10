#pragma once

namespace Scene {
class SceneBase {
public:
    virtual void start() = 0;
    virtual void update() = 0;
    virtual void end() = 0;
    virtual void draw() = 0;
    virtual ~SceneBase() = default;
};
}