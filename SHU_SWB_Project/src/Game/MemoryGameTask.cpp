/***************************************************************************************
*	Title: MemoryGameTask.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#include "MemoryGameTask.h"

#include "../Framework/EventManager/EventManager.h"
#include "../Framework\Collision\CollisionManager.h"
#include "../Framework\Renderer\Mesh\MeshManager.h"
#include "../WindowsPlatform/Renderer/Texture/TextureD3D.h"
#include "../WindowsPlatform/Renderer/Sprite/SpriteD3D.h"
#include "../WindowsPlatform/Input/DInputManager.h"
#include "../Framework/Utilities/Timer.h"
#include <algorithm>
#include <time.h>
#include "..\WindowsPlatform\WindowsPlatformTask.h"

MemoryGameTask::MemoryGameTask(const unsigned int priority) :Task(priority), pTraceHUD_(nullptr), cards_(16, nullptr), first_(nullptr), second_(nullptr), state_(WELCOME_SCREEN), textScreens_(), matchPending_(false), matchPendingDeltaTime_(0.0f) {

}

MemoryGameTask::~MemoryGameTask() {
    if (pTraceHUD_) {
        delete pTraceHUD_;
        pTraceHUD_ = nullptr;
    }

    for (unsigned int i(0); i < cards_.size(); ++i) {
        if (cards_.at(i)) {
            delete cards_.at(i);
            cards_.at(i) = nullptr;
        }
    }
}

void MemoryGameTask::placeCards() {
    float offset(1.2f);
    float x(-1.5f * offset), y(1.5f * offset);

    random_shuffle(cards_.begin(), cards_.end());

    // place the 16 cards
    for (int i(0); i < 16; ++i) {
        float xOffset((i % 4) * offset);
        float yOffset((i / 4) * offset);
        const Vector3 vec(Vector3(x + xOffset, y - yOffset, 0));
        cards_.at(i)->setPosition(vec);
        cards_.at(i)->reset();
    }
}

void MemoryGameTask::setupCard(TextureManager* textureManager, SpriteManager* spriteManager, Card* card, int cardId) {
    float u(0.0f), v(0.0f);
    // size of card as percentage of texture size, 1/8 in this case
    // TODO: add an accessor to texture dimentions
    float spriteSize(0.125f);

    SpriteD3D* pSprite(nullptr);

    // back of card
    pSprite = static_cast<SpriteD3D*>(spriteManager->getSprite(0));

    assert(pSprite);

    pSprite->setUVCoords(0, u, v);
    pSprite->setUVCoords(1, u + spriteSize, v);
    pSprite->setUVCoords(2, u + spriteSize, v + spriteSize);
    pSprite->setUVCoords(3, u, v + spriteSize);

    pSprite->setup(textureManager->getTexture(MEMORY_SPRITE.id), Sprite::SpriteAlign::CENTER, 1, 1);


    pSprite = nullptr;
    // face of card, according to id
    pSprite = static_cast<SpriteD3D*>(spriteManager->getSprite(cardId));
    assert(pSprite);

    int uMultiplier = cardId % 8;
    int vMultiplier = cardId / 8;
    u = spriteSize * uMultiplier;
    v = spriteSize * vMultiplier;

    pSprite->setUVCoords(0, u, v);
    pSprite->setUVCoords(1, u + spriteSize, v);
    pSprite->setUVCoords(2, u + spriteSize, v + spriteSize);
    pSprite->setUVCoords(3, u, v + spriteSize);

    pSprite->setup(textureManager->getTexture(MEMORY_SPRITE.id), Sprite::SpriteAlign::CENTER, 1, 1);

    card->setId(cardId);
    card->setup(pSprite);
}

bool MemoryGameTask::start() {
    registerEvent(UPDATE);
    registerEvent(POST_UPDATE);
    registerEvent(CLICKED_CARD);
    attachEvent(CLICKED_CARD, *this);

    textScreens_.onStart();
    state_ = WELCOME_SCREEN;

    pTraceHUD_ = new TraceHUD;

    // setup collision manager
    auto collisionManager(CollisionManager::getInstancePtr());
    assert(collisionManager);
    collisionManager->addCollisionGroup();

    //
    auto textureManager(TextureManager::getInstancePtr());
    assert(textureManager);
    textureManager->loadTexture<TextureD3D>(MEMORY_SPRITE);

    auto spriteManager(SpriteManager::getInstancePtr());
    assert(spriteManager);

    // setup objects

    camera_.setup();

    // add the 9 card sprites
    // 0 - back face
    // 1 to 8 - front faces
    for (int i(0); i < 9; ++i) {
        spriteManager->addSprite<SpriteD3D>(i);
    }

    vector<int> ids(16, 0);
    for (int i(0); i < 16; ++i) {
        ids.at(i) = (i % 8) + 1;
    }

    srand(time(NULL));
    random_shuffle(ids.begin(), ids.end());

    // create the 16 cards
    for (int i(0); i < 16; ++i) {
        cards_.at(i) = new Card;
        setupCard(textureManager, spriteManager, cards_.at(i), ids.at(i));
        collisionManager->addObjectToGroup(0, cards_.at(i));
    }

    return true;
}

void MemoryGameTask::onSuspend() {
    setSuspended(true);
}

void MemoryGameTask::update() {
    if (isSuspended()) return;

    camera_.update();

    auto input(DInputManager::getInstancePtr());
    assert(input);

    switch (state_) {
        case MemoryGameTask::IN_GAME_SCREEN:
        {
            auto collisionManager(CollisionManager::getInstancePtr());
            assert(collisionManager);
            collisionManager->testAgainstGroup(0, camera_.getMouseIndicatorPtr());
            int count(0);
            for (unsigned int i(0); i < cards_.size(); ++i) {
                cards_.at(i)->update();
                if (cards_.at(i)->isMatched()) {
                    ++count;
                }
            }

            // pending check for match
            if (matchPending_) {

                auto timer(Timer::getPtr());
                assert(timer);
                matchPendingDeltaTime_ += timer->getTimeSim();

                if (matchPendingDeltaTime_ >= 1.0f) {
                    checkForMatch();
                }
            }

            // check for gameOver
            if (count >= 16) {
                state_ = GAME_OVER_SCREEN;
                textScreens_.onGameOver();
            }
        }
        break;
        case MemoryGameTask::WELCOME_SCREEN:
        case MemoryGameTask::GAME_OVER_SCREEN:
            if (input->onKeyDown(DIK_SPACE)) {
                textScreens_.onPlay();
                placeCards();
                state_ = IN_GAME_SCREEN;
            }
            break;
        default:
            break;
    }

    if (input->onKeyDown(DIK_ESCAPE)) {
        sendEvent(APP_QUIT);
    }

    sendEvent(UPDATE);


    sendEvent(POST_UPDATE);
}

void MemoryGameTask::checkForMatch() {
    if (first_->getId() == second_->getId()) {
        first_->match();
        second_->match();
    } else {
        first_->flip();
        second_->flip();
    }
    first_ = nullptr;
    second_ = nullptr;

    matchPendingDeltaTime_ = 0.0f;
    matchPending_ = false;
}

void MemoryGameTask::handleEvent(Event* pEvent) {
    switch (pEvent->getID()) {
        case CLICKED_CARD:
        {
            if (!matchPending_) {
                Card* pCard = static_cast<Card*>(pEvent->getData());
                assert(pCard);
                if (!first_) {
                    first_ = pCard;
                    first_->flip();
                } else if (first_ == pCard) {
                    first_->flip();
                    first_ = nullptr;
                } else if (!second_) {
                    second_ = pCard;
                    second_->flip();
                    matchPending_ = true;
                }
            }
        }
        break;
        default:
            break;
    }
}

void MemoryGameTask::onResume() {
    setSuspended(false);
}

void MemoryGameTask::stop() {

}
