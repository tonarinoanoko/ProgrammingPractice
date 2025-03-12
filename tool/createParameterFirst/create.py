import requests
import pandas as pd
from io import StringIO
import sys
import os

# コマンドライン引数の処理
if len(sys.argv) < 2:
    print("Usage: python create.py <CSV_URL> [SHEET_GID]")
    sys.exit(1)

url = sys.argv[1]

# シートGIDの指定がある場合
if len(sys.argv) > 2:
    gid = sys.argv[2]
    url = url.replace("/edit", f"/export?format=csv&gid={gid}")
else:
    url = url.replace("/edit", "/export?format=csv")

response = requests.get(url)

# HTTPリクエストが成功したか確認
response.raise_for_status()

# CSVデータをStringIOを使ってpandasで読み込み
response.encoding = 'utf-8'
csv_data = StringIO(response.text)
df = pd.read_csv(csv_data, header=None)  # ヘッダ行なしで読み込み

# 1行目をファイル名として取得
_name = df.iloc[0, 0]
enum_name = df.iloc[2, 0]

# Enum用の.hファイルを生成する関数
def generate_enum_h_file(name, enum_name, file_name):
    if os.path.exists(f"{file_name}.h"):
        print(f"Skipping: {file_name} already exists.")
        return  # すでにファイルが存在する場合はスキップ

    #.hの作成
    with open(f"{file_name}.h", 'w') as file:
        file.write("#pragma once\n")
        file.write(f"#include \"ParameterBase.h\"\n")
        file.write(f"#include \"Enum/{enum_name}.h\"\n\n\n")
        file.write(f"namespace Parameter {{\n")
        file.write(f"namespace {name} {{\n")
        file.write(f"class ParameterData : public ParameterBase<{enum_name}::Enum>\n")
        file.write(f"{{\n")
        file.write(f"public:\n")
        file.write(f"    std::string _name;\n")
        file.write(f"    void makeParameter({enum_name}::Enum id) override;\n")
        file.write(f"}};\n")
        file.write(f"\n")
        file.write(f"inline auto& instance() {{\n")
        file.write(f"    return Parameters<{enum_name}::Enum, Parameter::{name}::ParameterData>::instance();\n")
        file.write(f"}}\n")
        file.write(f"}}}}  // namespace Parameter::{name}\n")

    #.cppの作成
    with open(f"{file_name}.cpp", 'w') as file:
        file.write(f"#include \"Parameter/{name}.h\"\n\n\n")
        file.write(f"namespace Parameter {{\n")
        file.write(f"namespace Monster {{\n")
        file.write(f"void ParameterData::makeParameter({enum_name}::Enum id)\n")
        file.write(f"{{\n")
        file.write(f"}}\n")
        file.write(f"}}}}  // namespace Parameter/{name}\n")

# Parameterを生成
file_name = f"../../src/Parameter/{_name}"
generate_enum_h_file(_name, enum_name, file_name)

print(f"Enum header file generated: {file_name}")
