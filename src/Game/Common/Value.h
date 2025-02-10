#pragma once
#include "Utility/Utility.h"


class Value
{
public:
    Value();
    Value(int value)
    {
        set(value);
    }
    Value(int value, int min, int max)
    {
        setMinMax(min, max);
        set(value);
    }

public:
    int const value() const { return _value; }

    void set(int value)
    {
        if(_use_min_max) {
            _value = Utility::Math::clamp(value, _min, _max);
        }
        else {
            _value = value;
        }
    }
    void add(int value) { set(_value + value); }

    void setMinMax(int min, int max)
    {
        _use_min_max = true;
        _min = min;
        _max = max;
    }

private:
    int _value = 0;
    bool _use_min_max = false;
    int _min = 0;
    int _max = 0;
};
