#include "Image.h"


namespace System{
explicit Image::Image(std::string const& file_path)
{
    load(file_path);
}

Image::~Image()
{
    if(_handle != -1) {
        DeleteGraph(_handle);
    }
}

void Image::load(std::string const& file_path)
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

void Image::draw(int x, int y, bool transparent = true) const
{
    if(_handle != -1) {
        DrawGraph(x, y, _handle, transparent);
    }
}

}  // namespace System
