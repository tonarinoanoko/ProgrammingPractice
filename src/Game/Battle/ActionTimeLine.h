#pragma once
#include <vector>
#include <Character/Character.h>


namespace Battle {
class ActionTimeLine
{
public:
    struct ActionEntry {
        int _character_id;
        int _action_time;
    };

public:
    ActionTimeLine(){};
    //void addAction(int characterId, int actionTime);
    //void update();  // 時間経過で行動可能キャラを処理

private:
    std::vector<ActionEntry> _time_line;
};

}  // namespace Battle
