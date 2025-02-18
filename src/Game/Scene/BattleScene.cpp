#include "BattleScene.h"

namespace Scene {
BattleScene::BattleScene()
{
    setSceneId(EScene::Enum::Battle);
    setNextSceneId(EScene::Enum::Main);
}

void BattleScene::start()
{
    Debug::debugLog("Start Battle Scene");
    _battle_manager.startBattle();
    _message_window.SetMessage("Battle Scene");

    _command_window.SetCommands({"攻撃", "防御", "逃げる"});
}

void BattleScene::update()
{
    _battle_manager.updateOneTrun();

    auto & message_manager = _battle_manager.messsageManager();
    if(message_manager.has()) {
        _message_window.SetMessage(message_manager.message());
        message_manager.clear();
    }
    _message_window.Update();
    _command_window.Update();

    auto const & input = System::InputManager::instance();
    if(input.isKeyDown(KEY_INPUT_Z)) {
        _is_end = true;
    }
}

void BattleScene::end()
{
}

void BattleScene::draw()
{
    _message_window.Draw();
    _command_window.Draw();
}

bool BattleScene::isEnd()
{
    return _is_end;
}
}  // Scene
