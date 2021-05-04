/***************************************************************************************
*	Title: SpriteAnimationComponent.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#include "SpriteAnimationComponent.h"
#include "../../EventManager/EventManager.h"
#include "../../Renderer/Renderer.h"
#include "../Components/TransformComponent.h"
#include "../Components/AABBColliderComponent.h"
#include "../GameObject.h"

namespace Framework {

    SpriteAnimationComponent::SpriteAnimationComponent(GameObject* pOwner) : Component(pOwner), animation_(25, 12) {
        attachEvent(RENDER_EVENT, *this);
        attachEvent(UPDATE, *this);
    }

    SpriteAnimationComponent::~SpriteAnimationComponent() {

    }

    void SpriteAnimationComponent::handleEvent(Event* pEvent) {
        switch (pEvent->getID()) {
            case RENDER_EVENT: {

                assert(Renderer::getPtr());

                AABBColliderComponent* pAABBComp = component_cast<AABBColliderComponent>(getOwner());

                if (pAABBComp) {
                    Renderer::getPtr()->drawAABB(pAABBComp->getMin() , pAABBComp->getMax(), ColorARGB(1.0f, 0.0f, 1.0f, 0.0f));
                }

                TransformComponent* transformComp = component_cast<TransformComponent>(getOwner());
                assert(transformComp);
                Transform& tr = transformComp->getTransform();

                tr.setMatrix();

                Renderer::getPtr()->setTransform(tr.getMatrix());

                animation_.render();
            }
            break;
            case UPDATE: {
                animation_.update();
            }
            break;
            default:
                break;
        }
    }

}
