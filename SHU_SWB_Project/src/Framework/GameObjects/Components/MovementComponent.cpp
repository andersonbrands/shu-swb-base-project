/***************************************************************************************
*	Title: MovementComponent.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#include "MovementComponent.h"
#include "TransformComponent.h"
#include "../GameObject.h"
#include "../../Utilities/Timer.h"

namespace Framework {

    MovementComponent::MovementComponent(GameObject* pOwner) :
        Component(pOwner), up_(0,1,0), forward_(0,0,1), right_(1,0,0), acceleration_(0), velocity_(0) {

    }

    void MovementComponent::setup(const Vector3& up, const Vector3& forward, const Vector3& right) {
        up_ = up ;
        forward_ = forward;
        right_ = right;
    }

    MovementComponent::~MovementComponent() {

    }

    const Vector3 MovementComponent::getUp() {
        return up_;
    }
    const Vector3 MovementComponent::getForward() {
        return forward_;
    }
    const Vector3 MovementComponent::getRight() {
        return right_;
    }
    const Vector3 MovementComponent::getAcceleration() {
        return acceleration_;
    }
    const Vector3 MovementComponent::getVelocity() {
        return velocity_;
    }

    void MovementComponent::setAcceleration(const Vector3& acceleration) {
        acceleration_ = acceleration;
    }
    void MovementComponent::setVelocity(const Vector3& velocity) {
        velocity_ = velocity;
    }

    void MovementComponent::accelerate(const Vector3& acc) {
        acceleration_ += acc;
    }
    void MovementComponent::accelerate(const Direction direction, float value) {
        switch (direction) {
            case Direction::FORWARD:
                accelerate(forward_ * value);
                break;
            case Direction::BACKWARD:
                accelerate(forward_ * (-value));
                break;
            case Direction::UP:
                accelerate(up_ * value);
                break;
            case Direction::DOWN:
                accelerate(up_ * (-value));
                break;
            case Direction::RIGHT:
                accelerate(right_ * value);
                break;
            case Direction::LEFT:
                accelerate(right_ * (-value));
                break;
            default:
                break;
        }
    }

    const Vector3 MovementComponent::move() {
        velocity_ += acceleration_;

        acceleration_ = Vector3(0.0f);

        TransformComponent* pTransformComp(component_cast<TransformComponent>(*getOwner()));
        assert(pTransformComp);
        Transform& tr(pTransformComp->getTransform());

        assert(Timer::getPtr());

        Vector3 result(velocity_ * Timer::getPtr()->getTimeSim());

        tr.translate(result);

        return result;
    }

}