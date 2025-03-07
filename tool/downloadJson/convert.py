import pandas as pd
import requests
from io import StringIO
import sys
import os

def fetch_and_convert(url, file_name, output_dir="../../src/Parameter/json"):
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    # Googleスプレッドシートの場合、CSVとしてエクスポート
    if "docs.google.com" in url:
        url = url.replace("/edit", "/export?format=csv")

    try:
        response = requests.get(url)
        response.raise_for_status()
        response.encoding = 'utf-8'
        csv_data = StringIO(response.text)
        df = pd.read_csv(csv_data, header=None)

        # 2行目をカラム名に設定（1行目をスキップ）
        df.columns = df.iloc[1]  
        df = df.iloc[2:].reset_index(drop=True)  # 3行目以降をデータとして扱う

        # JSONファイル名を決定（URLの一部を使用）
        json_name = f"{file_name}Parameter.json"
        file_path = os.path.join(output_dir, json_name)

        # JSONファイルとして出力
        df.to_json(file_path, orient="records", indent=4, force_ascii=False)

        print(f"成功: {file_path} にJSONを出力しました！")
    except Exception as e:
        print(f"エラー: データの取得に失敗しました - {e}")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("エラー: URLが指定されていません")
        sys.exit(1)

    url = sys.argv[1]
    file_name = sys.argv[2]
    fetch_and_convert(url, file_name)
