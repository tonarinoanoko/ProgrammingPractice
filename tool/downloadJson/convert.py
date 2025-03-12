import pandas as pd
import requests
from io import StringIO
import sys
import os

# データ型変換を行う関数
def apply_conversion_rules(df, types):
    for i, column in enumerate(df.columns):
        column_type = types[i]

        if column_type == 'int':
            df[column] = df[column].apply(lambda x: [pd.to_numeric(i, errors='coerce') for i in x] if isinstance(x, list) else pd.to_numeric(x, errors='coerce'))
        elif column_type == 'string':
            df[column] = df[column].apply(lambda x: [str(i) for i in x] if isinstance(x, list) else str(x))
        elif column_type == 'float':
            df[column] = df[column].apply(lambda x: [pd.to_numeric(i, errors='coerce') for i in x] if isinstance(x, list) else pd.to_numeric(x, errors='coerce'))
        elif column_type == 'bool':
            df[column] = df[column].apply(lambda x: [bool(i) for i in x] if isinstance(x, list) else bool(x))

    return df

def fetch_and_convert(url, file_name, output_dir="../../src/Parameter/json"):
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    try:
        response = requests.get(url)
        response.raise_for_status()
        response.encoding = 'utf-8'
        csv_data = StringIO(response.text)
        df = pd.read_csv(csv_data, header=None)

        # 1行目はスキップ
        # 2行目をデータ型として取得
        types = df.iloc[1].values  # 2行目にデータ型が格納されている

        # 3行目をカラム名に設定
        df.columns = df.iloc[2]  

        # 4行目以降をデータとして扱う
        df = df.iloc[3:].reset_index(drop=True)  

        # インデックス列を保存しておく
        index_column = df.columns[0]

        # ルールに基づいたデータ型変換を行う
        df = apply_conversion_rules(df, types)

        # 1列目をインデックスとして設定
        df.set_index(index_column, inplace=True)  # 1列目をインデックスに設定

        # JSONファイル名を決定（URLの一部を使用）
        json_name = f"{file_name}Parameter.json"
        file_path = os.path.join(output_dir, json_name)

        # JSONファイルとして出力（辞書型で出力）
        df.to_json(file_path, orient="index", indent=4, force_ascii=False)

        print(f"成功: {file_path} にJSONを出力しました！")
    except Exception as e:
        print(f"エラー: データの取得に失敗しました - {e}")

if __name__ == "__main__":

    # コマンドライン引数の処理
    if len(sys.argv) < 2:
        print("Usage: python create_enum.py <CSV_URL> <FILE_NAME> [SHEET_GID]")
        sys.exit(1)

    url = sys.argv[1]
    file_name = sys.argv[2]

    # シートGIDの指定がある場合
    if len(sys.argv) > 3:
        gid = sys.argv[3]
        url = url.replace("/edit", f"/export?format=csv&gid={gid}")
    else:
        url = url.replace("/edit", "/export?format=csv")

    fetch_and_convert(url, file_name)
