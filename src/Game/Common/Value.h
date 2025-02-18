#pragma once
#include <ostream>
#include "Utility/Utility.h"

#include "Debug/DebugLog.h"


class Value
{
public:
    explicit Value(int value = 0, int min = 0, int max = 9999)
    {
        setMinMax(min, max);
        set(value);
    }

public:
    int const value() const { return _value; }

    void set(int value)
    {
        _value = Utility::Math::clamp(value, _min, _max);
    }
    void add(int value) { set(_value + value); }

    void setMinMax(int min, int max)
    {
        Debug::assertLog(min <= max);
        _min = min;
        _max = max;
    }

public:
    bool operator==(Value const& other) const
    {
        return _value == other.value();
    }

    bool operator!=(Value const& other) const
    {
        return _value != other.value();
    }

    bool operator<(Value const& other) const
    {
        return _value < other.value();
    }

    bool operator>(Value const& other) const
    {
        return _value > other.value();
    }

    friend std::ostream& operator<<(std::ostream& os, const Value& v)
    {
        os << v._value;
        return os;
    }

private:
    int _value = 0;
    int _min = 0;
    int _max = 0;
};
