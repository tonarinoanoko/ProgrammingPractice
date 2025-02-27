#include "BattleScene.h"

#include "System/InputManager.h"
#include "Common/MessageManager.h"

namespace Scene {
BattleScene::BattleScene()
{
    setSceneId(EScene::Enum::Battle);
    setNextSceneId(EScene::Enum::Main);
}

void BattleScene::start()
{
    Debug::debugLog("Start Battle Scene");
    _battle_manager.startBattle(&_battle_ui_manager);

    _battle_ui_manager.messageWin().setMessage("Battle Scene");
}

void BattleScene::update()
{
    _battle_manager.update();

    auto & message_manager = _battle_manager.messsageManager();
    if(message_manager.has()) {
        _battle_ui_manager.messageWin().setMessage(message_manager.message());
        message_manager.clear();
    }
    _battle_ui_manager.update();
}

void BattleScene::end()
{
}

void BattleScene::draw()
{
    _battle_ui_manager.draw();
}

bool BattleScene::isEnd()
{
    if(_battle_manager.isFinishedBattle()) {
        Debug::debugLog("FinishedBattle");
        return true;
    }

    return false;
}
}  // Scene
