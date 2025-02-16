#pragma once


namespace PlayerData {
class PlayerData
{
private:
    PlayerData() {}

public:
    static PlayerData& instance() {
        static PlayerData _instance;
        return _instance;
    }

private:
    static PlayerData _instance;
};
}  // PlayerData
