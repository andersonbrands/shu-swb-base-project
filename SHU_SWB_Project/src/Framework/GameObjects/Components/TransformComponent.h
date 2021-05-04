/***************************************************************************************
*	Title: TransformComponent.h
*	Author: Brandao, Anderson
*	Date: 2014
*
*	Based on original by Bruce Sutherland available at http://www.apress.com/9781430258308 (2014)
*
***************************************************************************************/

#ifndef TRANSFORM_COMPONENT_H_
#define TRANSFORM_COMPONENT_H_

#include "../Component.h"
#include "../ComponentId.h"
#include "../../Math/Transform.h"

namespace Framework {
    class GameObject;

    class TransformComponent: public Component {
        public:
			static ComponentId getId() {
                return COMPONENT_ID_TRANSFORM;
            }

            explicit TransformComponent(GameObject* pOwner);
            virtual ~TransformComponent();

            Transform& getTransform() {
                return transform_;
            }
            const Transform& getTransform() const {
                return transform_;
            }
        private:
            Transform transform_;

    };
}

#endif // TRANSFORM_COMPONENT_H_
