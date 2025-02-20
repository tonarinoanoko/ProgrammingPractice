#include "ActionTimeLine.h"
#include <iostream>
#include <algorithm>

#include "Debug/DebugLog.h"


namespace Battle {
void ActionTimeLine::addAction(ActionEntry entry)
{
    _time_line.emplace_back(entry);
}

void ActionTimeLine::eraseAction(int character_id)
{
    _time_line.erase(std::remove_if(_time_line.begin(), _time_line.end(),
        [character_id](ActionEntry const& entry) { return entry._character_id == character_id; }),
        _time_line.end());
}

void ActionTimeLine::eraseActionBegin()
{
    _time_line.erase(_time_line.begin());
}

ActionTimeLine::ActionEntry const& ActionTimeLine::actionEntry() const
{
    Debug::assertLog(_time_line.size() > 0, "_time_line の要素が0");
    if (_time_line.empty()) {
        throw std::out_of_range("_time_line is empty");
    }

    return _time_line.front();  // 先頭の要素を返す
}

bool ActionTimeLine::update()
{
    for(auto & entry : _time_line) {
        entry._action_time -= entry._cool_time;
    }

    std::sort(_time_line.begin(), _time_line.end(), [] (ActionEntry const& a, ActionEntry const& b)
    {
        return std::tie(a._action_time, a._character_id) < std::tie(b._action_time, b._character_id);
    });

    return actionEntry()._action_time == 0;
}
}  // namespace Battle
