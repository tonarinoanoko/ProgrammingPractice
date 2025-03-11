#include "Parameter/Monster.h"

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include "Debug/GameDebug.h"
#include <filesystem>

namespace Parameter {
namespace Monster {
void ParameterData::makeParameter(EMonsterId::Enum id)
{
    std::ifstream file("./src/Parameter/json/MonsterParameter.json");  // JSONファイルを開く
    if (Debug::assertLog(file.fail() == false, "ファイルを開けませんでした。") == false) {
        return;
    }

    nlohmann::json json_data;
    file >> json_data;  // JSONデータを読み込む

    auto id_str = EnumToString(id);
    std::cout << id_str << std::endl;
    if (json_data.contains(id_str)) {
        auto data = json_data[id_str];
        _name = data["name"];
        int hp = data["hp"].get<int>();
        int atk = data["attack"].get<int>();
        int def = data["def"].get<int>();
        int spd = data["speed"].get<int>();

        auto status_map = Character::UStatusMap();
        status_map[EStatus::Enum::Hp].set(hp);
        status_map[EStatus::Enum::Atk].set(atk);
        status_map[EStatus::Enum::Def].set(def);
        status_map[EStatus::Enum::Spd].set(spd);
        _status.setStatus(status_map);
    }
    else {
        Debug::debugLog("JsonDataの取得に失敗");
    }

    file.close();

}
}}  // namespace Parameter/Monster
