/***************************************************************************************
*	Title: CameraComponent.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#include "CameraComponent.h"
#include "TransformComponent.h"
#include "../../Renderer/Renderer.h"
#include "MovementComponent.h"
#include "../../EventManager/EventData.h"

namespace Framework {

    CameraComponent::CameraComponent(GameObject* pOwner) : Component(pOwner), frustum_() {
        attachEvent(PRE_RENDER_EVENT, *this);

        attachEvent(CAMERA_MOVE, *this);
    }
    CameraComponent::~CameraComponent() {
    }

    // getters and setters
    const Vector3 CameraComponent::getUpVector() const {
        auto mComp = component_cast<MovementComponent>(getOwner());
        assert(mComp);
        return mComp->getUp();
    }
    const Vector3 CameraComponent::getForwardVector() const {
        auto mComp = component_cast<MovementComponent>(getOwner());
        assert(mComp);
        return mComp->getForward();
    }
    const Vector3 CameraComponent::getRightVector() const {
        auto mComp = component_cast<MovementComponent>(getOwner());
        assert(mComp);
        return mComp->getRight();
    }

    void CameraComponent::updateFrustum() {
        const float halfHeight(tan(verticalFieldOfView_) * near_);
        const float halfWidth(aspectRatio_ * halfHeight);
        const Vector3 position(component_cast<TransformComponent>(getOwner())->getTransform().getTranslation());
        const Vector3 forward(getForwardVector());
        const Vector3 right(getRightVector());
        const Vector3 up(getUpVector());
        const Vector3 nearCenter(forward * near_ + position);

        // near plane
        frustum_.setPlane(Frustum::NEAR, nearCenter, getForwardVector());

        // far plane
        frustum_.setPlane(Frustum::FAR, forward * far_ + position, -getForwardVector());

        Vector3 normal;

        // top plane
        const Vector3 upToTop(getUpVector() * halfHeight);
        normal = ((nearCenter + upToTop) - position);
        normal = normal.cross(right);
        normal.normalise();
        frustum_.setPlane(Frustum::TOP, position, normal);

        // bottom plane
        normal = ((nearCenter + -upToTop) - position).cross(-getRightVector());
        normal.normalise();
        frustum_.setPlane(Frustum::BOTTOM, position, normal);

        // right plane
        normal = nearCenter + (right * halfWidth);
        normal -= position;
        normal = normal.cross(-up);
        normal.normalise();
        frustum_.setPlane(Frustum::RIGHT, position, normal);

        // left plane
        normal = nearCenter + (right * -halfWidth);
        normal -= position;
        normal = normal.cross(up);
        normal.normalise();
        frustum_.setPlane(Frustum::LEFT, position, normal);
    }

    void CameraComponent::handleEvent(Event* pEvent) {
        switch (pEvent->getID()) {
            case PRE_RENDER_EVENT: {

                assert(Renderer::getPtr());
                TransformComponent* transformComp = component_cast<TransformComponent>(getOwner());
                assert(transformComp);
                Transform& tr = transformComp->getTransform();

                Renderer::getPtr()->setupViewMatrices(tr.getTranslation(), tr.getTranslation() + getForwardVector(), getUpVector());
            }
            break;

            case CAMERA_MOVE: {
                MovementEventData* pMovementData = static_cast<MovementEventData*>(pEvent->getData());

                MovementComponent* pMvComp( component_cast<MovementComponent>( getOwner() ) );

                if (pMovementData && pMvComp) {
                    pMvComp->accelerate(pMovementData->direction, 15.0f);
                }
            }
            break;
            default:
                break;
        }
    }

}