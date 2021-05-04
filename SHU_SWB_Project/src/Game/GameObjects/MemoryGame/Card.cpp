/***************************************************************************************
*	Title: Card.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#include "Card.h"

#include "../../../Framework/Renderer/Sprite/SpriteManager.h"
#include "../../../Framework/Renderer/Texture/TextureManager.h"
#include "../../../WindowsPlatform/Renderer/Texture/TextureD3D.h"
#include "../../../Framework/GameObjects/Components/TransformComponent.h"
#include "../../../Framework/GameObjects/Components/SpriteAnimationComponent.h"
#include "../../../Framework/GameObjects/Components/AABBColliderComponent.h"
#include "../../../WindowsPlatform/Input/DInputManager.h"
#include "../../../Framework/EventManager/EventManager.h"
#include "../../../Framework/EventManager/EventData.h"

Card::Card() : matched_(false) {

}

Card::~Card() {

}

void Card::match() {
    matched_ = true;
    SpriteAnimationComponent* pAnimComp = component_cast<SpriteAnimationComponent>(this);
    pAnimComp->animation_.stop();
}

void Card::reset() {
    matched_ = false;
    SpriteAnimationComponent* pAnimComp = component_cast<SpriteAnimationComponent>(this);
    pAnimComp->animation_.goToAndPause(1);
}

void Card::flip() {
    SpriteAnimationComponent* pAnimComp = component_cast<SpriteAnimationComponent>(this);

    pAnimComp->animation_.goToAndPause((pAnimComp->animation_.getCurrentFrame()==1)?2:1);
}

void Card::handleEvent(Event* pEvent) {
    switch (pEvent->getID()) {
        case COLLISION_EVENT: {
            if (matched_) break;
            CollisionEventData* pData(static_cast<CollisionEventData*>(pEvent->getData()));
            assert(pData);
            if (pData->go1 == this || pData->go2 == this) {
                auto input(DInputManager::getInstancePtr());
                assert(input);
                if (input->onMouseLeftButtonDown()) {
                    sendEvent(CLICKED_CARD, this);
                }
            }
        }
        break;
        default:
            break;
    }
}

void Card::update() {

}

void Card::setPosition(const Vector3 &pos) {
    Transform& spriteTransform(component_cast<TransformComponent>(this)->getTransform());
    spriteTransform.setTranslation(pos);
}

void Card::setup(Sprite* pSprite) {
    addComponent<TransformComponent>();

    Transform& spriteTransform(component_cast<TransformComponent>(this)->getTransform());

    spriteTransform.setTranslation(Vector3(-1000));
    spriteTransform.setScale(Vector3(1.0f, 1.0f, 1.0f));
    spriteTransform.setRotation(Vector3(0.0f, 0.0f, 0.0f));

    addComponent<SpriteAnimationComponent>();

    SpriteAnimationComponent* pAnimComp = component_cast<SpriteAnimationComponent>(this);

    // the card will have two sprites the back of the card(first), and the front(second)
    pAnimComp->animation_ = SpriteAnimation(2, 24);

    auto spriteManager = SpriteManager::getInstancePtr();
    assert(spriteManager);

    pAnimComp->animation_.addFrame(spriteManager->getSprite(0));// zero is to be the id of the back of the card sprite
    pAnimComp->animation_.addFrame(pSprite);

    // pause on back frame
    pAnimComp->animation_.goToAndPause(1);

    addComponent<AABBColliderComponent>();

    attachEvent(COLLISION_EVENT, *this);
}
