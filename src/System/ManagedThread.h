#pragma once
#include <thread>
#include <memory>


namespace System {
// デストラクタでjoinを行う比較的安全なスレッド処理
// System::ManagedThread thread(関数, 引数);を呼び出しだらスレッド処理が開始される。
// 終了チェック時にisFinishedを呼ぶことで安全に終了したかをチェックできるので、確実に終了が約束されていない処理がある場合はチェックをしてから次に進むこと。
class ManagedThread {
public:
    // コンストラクタでスレッドを作成
    template <typename Function, typename... Args>
    explicit ManagedThread(Function&& func, Args&&... args) {
        _thread = std::make_unique<std::thread>(std::forward<Function>(func), std::forward<Args>(args)...);
    }

    // デストラクタでjoinを呼び出す
    ~ManagedThread() {
        if (_thread && _thread->joinable()) {
            _thread->join();  // スレッドがjoinableならjoin
        }
    }

    // スレッドを取得するメソッド
    std::thread& thread() {
        return *_thread;
    }

    // スレッドが終了したかどうかを確認するメソッド
    bool isFinished() const {
        return _thread == nullptr || _thread->joinable() == false; // スレッドが無効か、終了している場合
    }

private:
    std::unique_ptr<std::thread> _thread;
};
}  // namespace System
