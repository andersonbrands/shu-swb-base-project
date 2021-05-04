/***************************************************************************************
*	Title: AABBColliderComponent.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#include "AABBColliderComponent.h"

#include <cassert>
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "SpriteAnimationComponent.h"
#include "../GameObject.h"

namespace Framework {

    AABBColliderComponent::AABBColliderComponent(GameObject* pOwner) : Component(pOwner) {
        setAABB();
        attachEvent(POST_UPDATE, *this);
    }
    AABBColliderComponent::~AABBColliderComponent() {
    }

    void AABBColliderComponent::setAABB() {
        TransformComponent* transformComp = component_cast<TransformComponent>(getOwner());
        assert(transformComp);
        Transform& tr = transformComp->getTransform();

        MeshComponent<Mesh>* pMeshComp = component_cast<MeshComponent<Mesh>>(getOwner());

        if (pMeshComp) {
            aabb_.setMin(tr.getTranslation() + pMeshComp->getMin()* tr.getScale());
            aabb_.setMax(tr.getTranslation() + pMeshComp->getMax() * tr.getScale());
        }

        SpriteAnimationComponent* pSprite = component_cast<SpriteAnimationComponent>(getOwner());
        if (pSprite) {
            aabb_.setMin(tr.getTranslation() + pSprite->getMin()* tr.getScale());
            aabb_.setMax(tr.getTranslation() + pSprite->getMax()* tr.getScale());
        }
    }

    bool AABBColliderComponent::collides(const AABBColliderComponent* pTarget) {
        assert(pTarget);

        return aabb_.collides(pTarget->aabb_);
    }

    void AABBColliderComponent::handleEvent(Event* pEvent) {
        switch (pEvent->getID()) {
            case POST_UPDATE:
                setAABB();
                break;
            default:
                break;
        }
    }
}


