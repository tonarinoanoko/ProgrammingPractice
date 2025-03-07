import tkinter as tk
from tkinter import ttk, messagebox
import csv
import subprocess
import os

# CSVファイルからURLリストを読み込む
def load_url_list(filename):
    url_list = []
    try:
        with open(filename, "r", encoding="utf-8") as file:
            reader = csv.reader(file)
            url_list = [(row[0], row[1]) for row in reader if len(row) == 2]
    except FileNotFoundError:
        messagebox.showerror("エラー", f"{filename} が見つかりません")
    return url_list

# スクリプトを実行する関数
def execute_script():
    selected_index = listbox.curselection()
    if not selected_index:
        messagebox.showwarning("警告", "リストからURLを選択してください")
        return
    
    selected_name, selected_url = url_list[selected_index[0]]
    
    try:
        # スクリプトのディレクトリを取得
        script_dir = os.path.dirname(os.path.abspath(__file__))
        script_path = os.path.join(script_dir, "create.py")

        # create_enum.py をスクリプトディレクトリで実行
        subprocess.run(["python", script_path, selected_url], check=True, cwd=script_dir)
        messagebox.showinfo("成功", f"{selected_name} のEnumヘッダファイルを作成しました")
    except subprocess.CalledProcessError:
        messagebox.showerror("エラー", "スクリプトの実行に失敗しました")

# GUIの作成
root = tk.Tk()
root.title("Enum ヘッダ作成ツール")

# スクリプトのディレクトリを基準にファイルパスを取得
script_dir = os.path.dirname(os.path.abspath(__file__))
csv_file = os.path.join(script_dir, "../urls.csv")

# URLリストを読み込む
url_list = load_url_list(csv_file)

# リスト表示
frame = ttk.Frame(root, padding=10)
frame.pack(fill=tk.BOTH, expand=True)

label = ttk.Label(frame, text="作成したいリストを選択してください")
label.pack()

listbox = tk.Listbox(frame, height=10)
for name, _ in url_list:
    listbox.insert(tk.END, name)
listbox.pack(fill=tk.BOTH, expand=True)

# 実行ボタン
button = ttk.Button(frame, text="作成", command=execute_script)
button.pack(pady=10)

# GUIを実行
root.mainloop()
