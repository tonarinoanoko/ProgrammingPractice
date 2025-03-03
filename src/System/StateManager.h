#pragma once

namespace System {

template<typename T>
class StateManager
{
public:
    StateManager(T state) : _current(state), _previous(state) {}

    T current() const { return _current; }
    bool changed() const { return _changed; }

    void update() {
        _changed = _current != _previous;
        _previous = _current;
    }

    void change(T new_state) {
        if (_current != new_state) {
            _current = new_state;
        }
    }

private:
    T _current;
    T _previous;
    bool _changed;
};

}  // namespace System
