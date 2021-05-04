/***************************************************************************************
*	Title: CameraComponent.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef CAMERA_COMPONENT_H_
#define CAMERA_COMPONENT_H_

#include "../Component.h"
#include "../ComponentId.h"
#include "../GameObject.h"
#include "../../EventManager/EventHandler.h"
#include "../../EventManager/EventManager.h"
#include "../../Math/Vector3.h"
#include "../../Utilities/Frustum.h"

namespace Framework {

    class CameraComponent : public Component, public EventHandler {
        public:
            explicit CameraComponent(GameObject* pOwner);
            virtual ~CameraComponent();

            static ComponentId getId()	{
                return COMPONENT_ID_CAMERA;
            }

            virtual void handleEvent(Event* pEvent);

            // getters
            const Vector3 getUpVector() const;
            const Vector3 getForwardVector() const;
            const Vector3 getRightVector() const;

            void updateFrustum();

        private:
            float near_;
            float far_;
            float verticalFieldOfView_;
            float aspectRatio_;
            Frustum frustum_;
    };

}

#endif // CAMERA_COMPONENT_H_