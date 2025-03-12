import requests
import pandas as pd
from io import StringIO
import sys

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

print(f"create : {url}")

# CSVを取得
response = requests.get(url)
response.raise_for_status()
response.encoding = 'utf-8'

# CSVデータをDataFrameとして読み込み
csv_data = StringIO(response.text)
df = pd.read_csv(csv_data, header=None)  # ヘッダなしで読み込む

# 3行目をEnum名、4行目以降をEnum値とする
enum_name = df.iloc[2, 0]
enum_values = df.iloc[3:, 0].dropna().tolist()

# Enum用の.hファイルを生成する関数
def generate_enum_h_file(enum_name, enum_values, file_name):
    with open(file_name, 'w') as file:
        file.write("#pragma once\n\n")
        file.write(f"#include \"EnumBase.h\"\n\n")
        file.write(f"DEFINE_ENUM({enum_name}, \n")

        for i, value in enumerate(enum_values):
            file.write(f"{value}{',' if i < len(enum_values) - 1 else ''}\n")
        
        file.write(")\n")

# Enumを生成
file_name = f"../../src/Enum/{enum_name}.h"
generate_enum_h_file(enum_name, enum_values, file_name)

print(f"Enum header file generated: {file_name}")
