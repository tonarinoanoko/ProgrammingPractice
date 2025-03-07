#pragma once
#include <unordered_map>
#include <string>
#include <array>
#include "Debug/DebugLog.h"

// ParameterBaseクラスは抽象クラスとして宣言
template <typename EnumType>
class ParameterBase
{
public:
    virtual ~ParameterBase() = default;
    virtual void makeParameter(EnumType id) = 0;  // 戻り値を適切に設定
};

// Enum型に応じたパラメータを生成するテンプレートクラス
template <typename EnumType, typename ParameterType>
class Parameters
{
public:
    Parameters()
    {
        for (int i = 0; i < EnumMax<EnumType>(); ++i) {
            auto id = static_cast<EnumType>(i);
            if (id == EnumType::None || id == EnumType::Max) {
                continue;
            }
            _param_map[id] = makeParameterData(id);  // makeParameterを使ってパラメータを設定
        }
    }

    static Parameters& instance()
    {
        static Parameters _instance;
        return _instance;
    }

    const ParameterType& parameter(EnumType id) const
    {
        auto it = _param_map.find(id);
        if (it == _param_map.end()) {
            Debug::assertLog("Enum ID not found!");
            static ParameterType default_parameter;
            return default_parameter;
        }
        return it->second;
    }

private:
    // Enumに対応したパラメータデータを作成する関数
    ParameterType makeParameterData(EnumType id)
    {
        ParameterType param;
        param.makeParameter(id);
        return param;
    }

    std::unordered_map<EnumType, ParameterType> _param_map;
};
