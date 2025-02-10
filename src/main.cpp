#include "DxLib.h"
#include <string>
#include <cstdlib>
#include <ctime>

#include "Debug/DebugLog.h"
#include "System/InputManager.h"
#include "Game/Scene/SceneManager.h"


bool sGameRunning = true;  // ゲームが実行中かどうか

// ゲームの初期化処理
void initGame() {
    // ここにゲームの初期化処理を追加
    // 例: 画像やサウンドのロード、初期設定など

    SetUseCharCodeFormat( DX_CHARCODEFORMAT_UTF8 );
    ChangeFont( _T("MS 明朝" ));

    Scene::SceneManager::getInstance().changeScene(Scene::SceneManager::EScene::Main);

    std::srand(std::time(0));

    Debug::debugLog("ゲーム開始");
}

// ゲームの終了処理
void endGame() {
    // ここにゲーム終了時の処理を追加
    // 例: リソースの解放など
}

// ゲームの状態を更新する処理
void updateGame() {
    // キー入力の状態を更新
    auto& input = System::InputManager::getInstance();
    input.update();

    // 入力処理（キーボード入力など）
    if (input.isKeyDown(KEY_INPUT_ESCAPE)) {
        sGameRunning = false;  // ESCキーで終了
    }

    Scene::SceneManager::getInstance().update();
}

int main() {
    // DxLibの初期化
    ChangeWindowMode(TRUE);  // ウィンドウモード
    DxLib_Init();            // DxLibの初期化
    SetWindowSize(1280, 720);  // 幅1280px, 高さ720px
    SetDrawScreen(DX_SCREEN_BACK);  // 描画先をバック画面に設定
    
    // ゲームの初期化
    initGame();

    // メインループ
    while (sGameRunning) {
        // メッセージ処理（ウィンドウの閉じる処理等）
        if (ProcessMessage() != 0) {
            sGameRunning = false;  // ゲーム終了のフラグを立てる
        }

        ClearDrawScreen();

        // ゲームの状態更新
        updateGame();

        ScreenFlip();
    }

    // ゲームの終了処理
    endGame();
    
    // DxLibの終了
    DxLib_End();
    
    return 0;
}
