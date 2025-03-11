#pragma once
#include <vector>
#include "Character/Character.h"


namespace Battle {
class ActionTimeLine
{
public:
    struct ActionEntry {
        int _character_id;  // 行動するキャラクターID
        int _action_time;   // 現在の行動時間
        int _cool_time;     // 行動時間のクールタイム
        std::string _name;  // 行動するキャラクター名
    };

public:
    ActionTimeLine(){};
    void addAction(Character::CharacterData const& character, int action_time, int cool_time);
    void eraseAction(int character_id);
    ActionEntry const& actionEntry() const;
    std::vector<ActionEntry> const& actionEntrys() const { return _entrys; }

    bool update();  // 行動可能なキャラが見つかったらtrue

private:
    std::vector<ActionEntry> _entrys;
};

}  // namespace Battle
