/***************************************************************************************
*	Title: SpriteExplosion.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#include "SpriteExplosion.h"
#include "../../Framework/Renderer/Sprite/SpriteManager.h"
#include "../../Framework/Renderer/Texture/TextureManager.h"
#include "../../WindowsPlatform/Renderer/Texture/TextureD3D.h"
#include "../../WindowsPlatform/Renderer/Sprite/SpriteD3D.h"
#include "../../Framework/GameObjects/Components/TransformComponent.h"
#include "../../Framework/GameObjects/Components/SpriteAnimationComponent.h"
#include "../../Framework/GameObjects/Components/AABBColliderComponent.h"

SpriteExplosion::SpriteExplosion() {

}

SpriteExplosion::~SpriteExplosion() {

}

void SpriteExplosion::setup() {
    assert(TextureManager::getInstancePtr());
    TextureManager::getInstancePtr()->loadTexture<TextureD3D>(EXPLOSION_SPRITE);

    addComponent<TransformComponent>();

    Transform& spriteTransform(component_cast<TransformComponent>(this)->getTransform());

    spriteTransform.setTranslation(Vector3(0.0f, 4.0f, 0.0f));
    spriteTransform.setScale(Vector3(2.0f, 2.0f, 1.0f));
    spriteTransform.setRotation(Vector3(0.0f, 0.0f, 0.0f));

    assert(addComponent<SpriteAnimationComponent>());
    SpriteAnimationComponent* pAnimComp = component_cast<SpriteAnimationComponent>(this);
    pAnimComp->animation_ = SpriteAnimation(25, 24);

    SpriteD3D* sprite;

    float u(0.0f), v(0.0f);
    int id(0);

    assert(SpriteManager::getInstancePtr());

    for (int i(0); i < 5; i++) {
        for (int j(0); j < 5; j++) {
            u = j * 0.2f;
            v = i * 0.2f;

            sprite = SpriteManager::getInstancePtr()->addSprite<SpriteD3D>(id++);

            sprite->setUVCoords(0, u, v);
            sprite->setUVCoords(1, u + 0.2f, v);
            sprite->setUVCoords(2, u + 0.2f, v + 0.2f);
            sprite->setUVCoords(3, u, v+ 0.2f);

            sprite->setup(TextureManager::getInstancePtr()->getTexture(EXPLOSION_SPRITE.id), Sprite::SpriteAlign::CENTER, 1, 1);

            pAnimComp->animation_.addFrame(sprite);
        }
    }

    pAnimComp->play();

    assert(addComponent<AABBColliderComponent>());
}

void SpriteExplosion::update() {

}

