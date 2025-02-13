#include "Status.h"


namespace Character {

int Status::statusInt(EStatus::Enum status_id) const
{
    auto it = _status.find(status_id);
    if (it != _status.end()) {
        return it->second.value();
    } else {
        return 0;
    }
}

Value& Status::statusValue(EStatus::Enum status_id)
{
    return _status[status_id];
}

void Status::setStatus(UStatusMap status)
{
    _status = status;
}


}  // Character
