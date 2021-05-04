/***************************************************************************************
*	Title: AABBColliderComponent.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef AABB_COLLIDER_COMPONENT_H_
#define AABB_COLLIDER_COMPONENT_H_

#include "../Component.h"
#include "../ComponentId.h"
#include "../../Collision/AABB.h"
#include "../../Math/Vector3.h"
#include "../../EventManager/EventHandler.h"
#include "../../EventManager/Event.h"

namespace Framework {

    class AABBColliderComponent : public Component, public EventHandler {
        public:
            AABBColliderComponent(GameObject* pOwner);
            ~AABBColliderComponent();

            static ComponentId getId()	{
                return COMPONENT_ID_AABB_COLLIDER;
            }


            virtual void handleEvent(Event* pEvent);

            const Vector3 getMin() {
                return aabb_.getMin();
            }

            const Vector3 getMax() {
                return aabb_.getMax();
            }

            bool collides(const AABBColliderComponent*);

        private:
            AABB aabb_;

            void setAABB();
    };

}

#endif // AABB_COLLIDER_COMPONENT_H_
