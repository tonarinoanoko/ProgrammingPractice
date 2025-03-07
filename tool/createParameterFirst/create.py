import requests
import pandas as pd
from io import StringIO
import sys
import os

# コマンドライン引数からURLを受け取る
if len(sys.argv) < 2:
    print("Usage: python create_enum.py <CSV_URL>")
    sys.exit(1)

url = sys.argv[1]

# CSVをURLから取得する
if "docs.google.com" in url:
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
enum_name = df.iloc[1, 0]

# Enum用の.hファイルを生成する関数
def generate_enum_h_file(name, enum_name, file_name):
    if os.path.exists(file_name):
        print(f"Skipping: {file_name} already exists.")
        return  # すでにファイルが存在する場合はスキップ

    with open(file_name, 'w') as file:
        file.write("#pragma once\n\n")
        file.write(f"#include \"ParameterBase.h\"\n")
        file.write(f"#include \"{enum_name}.h\"\n\n")
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

# Parameterを生成
file_name = f"../../src/Parameter/{_name}.h"
generate_enum_h_file(_name, enum_name, file_name)

print(f"Enum header file generated: {file_name}")
