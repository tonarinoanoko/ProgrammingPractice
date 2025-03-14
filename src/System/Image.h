#include "DxLib.h"
#include <string>

#include "Utility/ConvertString.h"


namespace System{
class Image {
public:
    explicit Image() {}
    // コンストラクタ（画像の読み込み）
    explicit Image(std::string const& file_path)
    {
        load(file_path);
    }

    // デストラクタ（自動的に破棄）
    ~Image()
    {
        if(_handle != -1) {
            DeleteGraph(_handle);
        }
    }

    // 画像の読み込み
    void load(std::string const& file_path)
    {
        if(_handle != -1) {
            return;
        }

        auto file_path_w = Utility::Conv::convertToStrTCHAR(file_path);
        _handle = LoadGraph(file_path_w.c_str());
        if(_handle == -1) {
            // 画像の読み込み失敗
            printf("Failed to load image: %s\n", file_path.c_str());
        }
    }

    // コピー禁止（同じハンドルを持つと2回 DeleteGraph される危険がある）
    Image(Image const&) = delete;
    Image& operator=(Image const&) = delete;

    // ムーブコンストラクタ
    Image(Image&& other) noexcept
    {
        _handle = other._handle;
        other._handle = -1;  // 移動元のハンドルを無効化
    }

    // ムーブ代入演算子
    Image& operator=(Image&& other) noexcept
    {
        if(this != &other) {
            if(_handle != -1) {
                DeleteGraph(_handle);
            }
            _handle = other._handle;
            other._handle = -1;
        }
        return *this;
    }

    // 画像の描画
    void draw(int x, int y, bool transparent = true) const
    {
        if(_handle != -1) {
            DrawGraph(x, y, _handle, transparent);
        }
    }

    // ハンドル取得
    int handle() const { return _handle; }

private:
    int _handle = -1;
};
}  // namespace System
