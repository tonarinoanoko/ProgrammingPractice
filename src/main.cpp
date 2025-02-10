#include "DxLib.h"
#include <string>

#include "Debug/DebugLog.h"
#include "System/InputManager.h"
#include "Game/Scene/SceneManager.h"

#include "Utility/Utility.h"


bool gameRunning = true;  // ゲームが実行中かどうか

// ゲームの初期化処理
void InitGame() {
    // ここにゲームの初期化処理を追加
    // 例: 画像やサウンドのロード、初期設定など

    SetUseCharCodeFormat( DX_CHARCODEFORMAT_UTF8 );
    ChangeFont( _T("MS 明朝" ));

    Scene::SceneManager::GetInstance().ChangeScene(Scene::SceneManager::EScene::Main);

    Debug::DebugLog("ゲーム開始");

    auto value = Utility::Math::Clamp(100, 0, 50);
}

// ゲームの終了処理
void EndGame() {
    // ここにゲーム終了時の処理を追加
    // 例: リソースの解放など
}

// ゲームの状態を更新する処理
void UpdateGame() {
    // キー入力の状態を更新
    auto& input = System::InputManager::GetInstance();
    input.Update();

    // 入力処理（キーボード入力など）
    if (input.IsKeyDown(KEY_INPUT_ESCAPE)) {
        gameRunning = false;  // ESCキーで終了
    }

    Scene::SceneManager::GetInstance().Update();
}

int main() {
    // DxLibの初期化
    ChangeWindowMode(TRUE);  // ウィンドウモード
    DxLib_Init();            // DxLibの初期化
    SetWindowSize(1280, 720);  // 幅1280px, 高さ720px
    SetDrawScreen(DX_SCREEN_BACK);  // 描画先をバック画面に設定
    
    // ゲームの初期化
    InitGame();

    // メインループ
    while (gameRunning) {
        // メッセージ処理（ウィンドウの閉じる処理等）
        if (ProcessMessage() != 0) {
            gameRunning = false;  // ゲーム終了のフラグを立てる
        }

        ClearDrawScreen();

        // ゲームの状態更新
        UpdateGame();

        ScreenFlip();
    }

    // ゲームの終了処理
    EndGame();
    
    // DxLibの終了
    DxLib_End();
    
    return 0;
}
