#include "Parameter/Monster.h"

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include "Debug/GameDebug.h"

namespace Parameter {
namespace Monster {
void ParameterData::makeParameter(EMonsterId::Enum id)
{
    std::ifstream file("json/MonsterParameter.json");  // JSONファイルを開く
    if (Debug::assertLog(file.fail() == false, "ファイルを開けませんでした。") == false) {
        return;
    }

    nlohmann::json json_data;
    file >> json_data;  // JSONデータを読み込む

    auto id_str = EMonsterId::EnumToString(id);
    if (Debug::assertLog(json_data.contains(id_str), "non data" + *id_str.data())) {
        auto data = json_data[id_str];
        _name = data["name"];
        int hp = data["hp"];
        int atk = data["attack"];
        int def = data["def"];
        int spd = data["speed"];

        auto status_map = Character::UStatusMap();
        status_map[EStatus::Enum::Hp].set(hp);
        status_map[EStatus::Enum::Atk].set(atk);
        status_map[EStatus::Enum::Def].set(def);
        status_map[EStatus::Enum::Spd].set(spd);
        _status.setStatus(status_map);
    }

}
}}  // namespace Parameter/Monster
