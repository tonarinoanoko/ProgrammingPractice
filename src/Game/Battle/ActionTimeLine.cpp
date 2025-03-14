#include "ActionTimeLine.h"
#include <iostream>
#include <algorithm>

#include "Debug/GameDebug.h"


namespace Battle {
void ActionTimeLine::addAction(Character::CharacterData const& character, int action_time, int cool_time)
{
    ActionTimeLine::ActionEntry new_entry {character.characterId(), action_time, cool_time, character.name()};
    _entrys.emplace_back(new_entry);
}

void ActionTimeLine::eraseAction(int character_id)
{
    _entrys.erase(std::remove_if(_entrys.begin(), _entrys.end(),
        [character_id](ActionEntry const& entry) {
            return entry._character_id == character_id;
        }),_entrys.end());
}

ActionTimeLine::ActionEntry const& ActionTimeLine::actionEntry() const
{
    Debug::assertLog(_entrys.size() > 0, "_entrys の要素が0");
    if (_entrys.empty()) {
        throw std::out_of_range("_entrys is empty");
    }

    return _entrys.front();  // 先頭の要素を返す
}

bool ActionTimeLine::update()
{
    for(auto & entry : _entrys) {
        entry._action_time -= entry._cool_time;
        entry._action_time = std::max(0, entry._action_time);
    }

    std::sort(_entrys.begin(), _entrys.end(), [] (ActionEntry const& a, ActionEntry const& b)
    {
        return std::tie(a._action_time, a._character_id) < std::tie(b._action_time, b._character_id);
    });

    return actionEntry()._action_time <= 0;
}
}  // namespace Battle
