/***************************************************************************************
*	Title: Camera.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#include "Camera.h"

#include "../../Framework/GameObjects/Components/TransformComponent.h"
#include "../../Framework/GameObjects/Components/MovementComponent.h"
#include "../../Framework/GameObjects/Components/CameraComponent.h"
#include "../../WindowsPlatform/Input/DInputManager.h"

Camera::Camera() {

}

Camera::~Camera() {

}

void Camera::setup() {
    addComponent<TransformComponent>();
    Transform& cameraTransform(component_cast<TransformComponent>(this)->getTransform());
    cameraTransform.setTranslation(Vector3(0.0f, 0.0f, -7.0f));

    addComponent<CameraComponent>();
    CameraComponent* pCameraComp = component_cast<CameraComponent>(this);

    assert(addComponent<MovementComponent>());
    component_cast<MovementComponent>(this)->setup(Vector3(0, 1, 0), Vector3(0, 0, 1), Vector3(1,0,0));

    mIndicator_.setup();
}

void Camera::update() {
    auto input = DInputManager::getInstancePtr();
    assert(input);

    auto& mIndicatorTransform = component_cast<TransformComponent>(mIndicator_)->getTransform();
    auto movementComp = component_cast<MovementComponent>(this);

    mIndicatorTransform.translate(movementComp->move());

    if (input->getDeltaX()) {
        mIndicatorTransform.translate(movementComp->getRight() * input->getDeltaX());
    }
    if (input->getDeltaY()) {
        mIndicatorTransform.translate(movementComp->getUp() * -input->getDeltaY());
    }

    Vector3 camPos(component_cast<TransformComponent>(this)->getTransform().getTranslation());

    mouseVec_ = mIndicatorTransform.getTranslation();
    mouseVec_ -= camPos;
    mouseVec_.normalise();
}
