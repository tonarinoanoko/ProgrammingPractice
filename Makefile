# コンパイラ
CXX = g++

# ソースファイルを自動取得（サブディレクトリも含む）
SRC = $(wildcard src/*.cpp) $(wildcard src/**/*.cpp) $(wildcard src/**/**/*.cpp)

# 出力ファイル
OUT = bin/main.exe

# インクルードとライブラリの設定
CXXFLAGS = -I include -L lib -I src -DDX_GCC_COMPILE
LIBS = -lDxLib -lDxUseCLib -lDxDrawFunc -ljpeg -lpng -lzlib -ltiff -ltheora_static -lvorbis_static -lvorbisfile_static -logg_static -lbulletdynamics -lbulletcollision -lbulletmath -lopusfile -lopus -lsilk_common -lcelt -lws2_32 -lwinmm -lgdi32

# ビルドルール
$(OUT): $(SRC)
	@if not exist bin (mkdir bin)
	$(CXX) $(SRC) -o $(OUT) $(CXXFLAGS) $(LIBS)

# クリーンアップ
clean:
	rm -f $(OUT)
