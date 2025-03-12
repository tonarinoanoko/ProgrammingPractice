#include "Parameter/Skill.h"
#include <fstream>
#include <nlohmann/json.hpp>


namespace Parameter {
namespace Skill {

// todo 外部から情報を得られるようにする。
void ParameterData::makeParameter(ESkillId::Enum id)
{
    std::ifstream file("./src/Parameter/json/SkillIdParameter.json");  // JSONファイルを開く
    if (Debug::assertLog(file.fail() == false, "ファイルを開けませんでした。") == false) {
        return;
    }

    nlohmann::json json_data;
    file >> json_data;  // JSONデータを読み込む

    auto id_str = EnumToString(id);
    if (json_data.contains(id_str)) {
        auto data = json_data[id_str];
        _name = data["name"];
        std::string type = data["type"];
        std::string target = data["target"];

        _skill_type = StringToEnum<ESkillType::Enum>(type);
        _skill_target = StringToEnum<ESkillTarget::Enum>(target);
    }
    else {
        Debug::debugLog("JsonDataの取得に失敗");

        _name = "None";
        _skill_type = ESkillType::Enum::None;
        _skill_target = ESkillTarget::Enum::None;
    }

    file.close();
}

}}  // namespace Parameter::Skill