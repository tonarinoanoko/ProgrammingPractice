import os
from PIL import Image

def resize_image_keep_aspect(input_path, output_path, base_width):
    """画像の比率を維持しながら幅を基準にリサイズ"""
    with Image.open(input_path) as img:
        w_percent = base_width / float(img.width)
        new_height = int(float(img.height) * w_percent)
        resized_img = img.resize((base_width, new_height), Image.LANCZOS)
        resized_img.save(output_path)
        print(f"Resized image saved to: {output_path}")

def batch_resize_images(input_folder, output_folder, base_width):
    """フォルダ内の全画像をリサイズ"""
    os.makedirs(output_folder, exist_ok=True)

    for filename in os.listdir(input_folder):
        if filename.lower().endswith((".png", ".jpg", ".jpeg", ".bmp", ".gif")):
            input_path = os.path.join(input_folder, filename)
            output_path = os.path.join(output_folder, filename)
            resize_image_keep_aspect(input_path, output_path, base_width)

batch_resize_images("tool/resizeTexture/input", "tool/resizeTexture/output", 120)
