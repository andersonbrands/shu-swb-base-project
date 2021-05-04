/***************************************************************************************
*	Title: GameTask.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#include "GameTask.h"
#include "../Framework/EventManager/EventManager.h"
#include "../Framework\Collision\CollisionManager.h"
#include "../Framework\Renderer\Mesh\MeshManager.h"
#include "../Framework/Audio/AudioManager.h"
#include "../WindowsPlatform\Audio\WaveDBuffer.h"

GameTask::GameTask(const unsigned int priority)
    :	Task(priority), pTraceHUD_(nullptr), dice_(), light_(), camera_(), floor1_(), spriteAnimation_() {

}

GameTask::~GameTask() {
    if (pTraceHUD_) {
        delete pTraceHUD_;
        pTraceHUD_ = nullptr;
    }
}

bool GameTask::start() {
    registerEvent(UPDATE);
    registerEvent(POST_UPDATE);

    pTraceHUD_ = new TraceHUD;

    // setup floor
    floor1_.setup();

    // setup dice
    dice_.setup();

    // setup light
    light_.setup();


    // setup camera
    camera_.setup();

    // setup collision manager
    assert(CollisionManager::getInstancePtr());
    CollisionManager::getInstancePtr()->addCollisionGroup();
    CollisionManager::getInstancePtr()->addObjectToGroup(0, &floor1_);
    CollisionManager::getInstancePtr()->addObjectToGroup(0, &dice_);

    // setup sounds
    assert(AudioManager::getPtr());
    WaveDBuffer* pWave = AudioManager::getPtr()->loadSound<WaveDBuffer>(LASER);

    pWave->load(AudioManager::getPtr()->getDir() + LASER.name);

    //AudioManager::getPtr()->play(LASER.id, 1.0f, true);

    // load texture
    spriteAnimation_.setup();

    return true;
}

void GameTask::onSuspend() {
    setSuspended(true);
}

void GameTask::update() {
    if (isSuspended()) return;

    dice_.update();

    camera_.update();

    sendEvent(UPDATE);

    CollisionManager::getInstancePtr()->testAgainstGroup(0, &dice_);

    sendEvent(POST_UPDATE);
}

void GameTask::onResume() {
    setSuspended(false);
}

void GameTask::stop() {

}
