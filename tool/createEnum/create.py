import requests
import pandas as pd
from io import StringIO
import sys

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

# 1行目をEnum名として取得
enum_name = df.iloc[1, 0]

# 残りの行をEnum値として取得
enum_values = df.iloc[2:, 0].dropna().tolist()

# Enum用の.hファイルを生成する関数
def generate_enum_h_file(enum_name, enum_values, file_name):
    with open(file_name, 'w') as file:
        file.write("#pragma once\n\n")
        file.write(f"#include \"EnumBase.h\"\n\n")
        file.write(f"DEFINE_ENUM({enum_name}, \n")
        
        # 最後の要素にはカンマをつけない
        for i, value in enumerate(enum_values):
            if i == len(enum_values) - 1:
                file.write(f"{value}\n")  # 最後の要素
            else:
                file.write(f"{value}, \n")  # その他の要素
        
        file.write(")\n")

# Enumを生成
file_name = f"../../src/Enum/{enum_name}.h"  # f-stringでファイル名を作成
generate_enum_h_file(enum_name, enum_values, file_name)

print(f"Enum header file generated: {file_name}")
