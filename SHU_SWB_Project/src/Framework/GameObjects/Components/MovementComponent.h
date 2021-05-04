/***************************************************************************************
*	Title: MovementComponent.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#include "../Component.h"
#include "../ComponentId.h"
#include "../../Math/Vector3.h"
#include "../../Utilities/Utils.h"

#ifndef MOVEMENT_COMPONENT_H_
#define MOVEMENT_COMPONENT_H_

namespace Framework {

    class MovementComponent : public Component {
        private:
            Vector3 up_;
            Vector3 forward_;
            Vector3 right_;
            Vector3 acceleration_;
            Vector3 velocity_;

        public:
            explicit MovementComponent(GameObject* pOwner);

            virtual ~MovementComponent();

            static ComponentId getId() {
                return COMPONENT_ID_MOVEMENT;
            }

            void setup(const Vector3& up, const Vector3& forward, const Vector3& right);

            const Vector3 getUp();
            const Vector3 getForward();
            const Vector3 getRight();
            const Vector3 getAcceleration();
            const Vector3 getVelocity();

            void setAcceleration(const Vector3& acceleration);
            void setVelocity(const Vector3& velocity);

			// TODO: consider using Force intead of acceleration
            void accelerate(const Vector3& acc);
            void accelerate(const Direction direction, float value);

			const Vector3 move();
    };

}
#endif // MOVEMENT_COMPONENT_H_
