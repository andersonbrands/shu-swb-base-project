/***************************************************************************************
*	Title: MeshD3DComponent.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#include "MeshD3DComponent.h"

#include "../../Framework/Renderer/Renderer.h"
#include "../../Framework/GameObjects/Components/TransformComponent.h"
#include "../../Framework/GameObjects/GameObject.h"
#include "../../Framework/GameObjects/Components/AABBColliderComponent.h"

void MeshD3DComponent::handleEvent(Event* pEvent) {
    switch (pEvent->getID()) {
        case RENDER_EVENT: {
            if (!mesh_) break;

            assert(Renderer::getPtr());
            TransformComponent* transformComp = component_cast<TransformComponent>(getOwner());
            assert(transformComp);
            Transform& tr = transformComp->getTransform();

            tr.setMatrix();

            Renderer::getPtr()->setTransform(tr.getMatrix());
            mesh_->render();

            AABBColliderComponent* pAABBComp = component_cast<AABBColliderComponent>(getOwner());

            if (pAABBComp) {
                Renderer::getPtr()->drawAABB(pAABBComp->getMin() , pAABBComp->getMax(), ColorARGB(1.0f, 0.0f, 1.0f, 0.0f));
            }
        }
        break;
        default:
            break;
    }
}
