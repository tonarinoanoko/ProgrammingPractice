#pragma once
#include <map>
#include "Enum/EStatus.h"
#include "Common/Value.h"


namespace Character {
using UStatusMap = std::map<EStatus::Enum, Value>;

class Status
{
public:
    UStatusMap const& status() const { return _status; }
    int statusInt(EStatus::Enum status_id) const;

    Value& statusValue(EStatus::Enum status_id);

    void setStatus(UStatusMap status);

private:
    UStatusMap _status = {};
};

}  // Character
