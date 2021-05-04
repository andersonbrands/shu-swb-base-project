/***************************************************************************************
*	Title: GameApplication.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#include "GameApplication.h"

#include "../WindowsPlatform\WindowsPlatformTask.h"
#include "../WindowsPlatform\Renderer\DirectXRenderer.h"
#include "../WindowsPlatform\Utilities\TimerWindows.h"
#include "../Framework\EventManager\EventManager.h"
#include "../WindowsPlatform\Input\DInputManager.h"
#include "../Framework\Renderer\Mesh\MeshManager.h"
#include "../Framework\Collision\CollisionManager.h"
#include "../WindowsPlatform\Audio\DSoundManager.h"
#include "../Framework\Renderer\Texture\TextureManager.h"
#include "../Framework\Renderer\Sprite\SpriteManager.h"

GameApplication::GameApplication(): Application(), pGameTask_(nullptr) {

}

GameApplication::~GameApplication() {
    if (pGameTask_) {
        delete pGameTask_;
        pGameTask_ = nullptr;
    }
}

bool GameApplication::initialize() {
    bool success(true);

    createSingletons();

    assert(TimerWindows::getInstancePtr());
    kernel_.addTask(TimerWindows::getInstancePtr());

    assert(WindowsPlatformTask::getInstancePtr());
    kernel_.addTask(WindowsPlatformTask::getInstancePtr());

    assert(DInputManager::getInstancePtr());
    kernel_.addTask(DInputManager::getInstancePtr());


    assert(DirectXRenderer::getInstancePtr());
    kernel_.addTask(DirectXRenderer::getInstancePtr());

    pGameTask_ = new GameTask(Task::GAME_PRIORITY);
    kernel_.addTask(pGameTask_);

    return success;
}

void GameApplication::createSingletons() {
    new EventManager();
    new TimerWindows( Task::TIMER_PRIORITY );
    new WindowsPlatformTask( Task::PLATFORM_PRIORITY );
    new DInputManager( Task::INPUT_PRIORITY );
    new DSoundManager("bin/data/audio/");
    new DirectXRenderer( Task::RENDER_PRIORITY );
    new MeshManager("bin/data/");
    new CollisionManager();
    new TextureManager("bin/data/");
    new SpriteManager();
}
void GameApplication::destroySingletons() {
    assert(SpriteManager::getInstancePtr());
    delete SpriteManager::getInstancePtr();

    assert(TextureManager::getInstancePtr());
    delete TextureManager::getInstancePtr();

    assert(CollisionManager::getInstancePtr());
    delete CollisionManager::getInstancePtr();

    assert(MeshManager::getInstancePtr());
    delete MeshManager::getInstancePtr();

    assert(DirectXRenderer::getInstancePtr());
    delete DirectXRenderer::getInstancePtr();

    assert(DSoundManager::getInstancePtr());
    delete DSoundManager::getInstancePtr();

    assert(DInputManager::getInstancePtr());
    delete DInputManager::getInstancePtr();

    assert(WindowsPlatformTask::getInstancePtr());
    delete WindowsPlatformTask::getInstancePtr();

    assert(TimerWindows::getInstancePtr());
    delete TimerWindows::getInstancePtr();

    assert(EventManager::getInstancePtr());
    delete EventManager::getInstancePtr();
}