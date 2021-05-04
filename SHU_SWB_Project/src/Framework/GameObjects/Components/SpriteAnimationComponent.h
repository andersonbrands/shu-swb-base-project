/***************************************************************************************
*	Title: SpriteAnimationComponent.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef SPRITE_ANIMATION_COMPONENT_H_
#define SPRITE_ANIMATION_COMPONENT_H_

#include "../Component.h"
#include "../ComponentId.h"
#include "../../Renderer/Sprite/SpriteAnimation.h"
#include "../../EventManager/EventHandler.h"
#include "../../EventManager/Event.h"

namespace Framework {

    class SpriteAnimationComponent : public Component, public EventHandler {
        private:
        public:
            explicit SpriteAnimationComponent(GameObject* pOwner);
            virtual ~SpriteAnimationComponent();

            static ComponentId getId()	{
                return COMPONENT_ID_SPRITE_ANIMATION;
            }

            SpriteAnimation animation_;

            void play() {
                animation_.play();
            }
            void pause() {
                animation_.pause();
            }
            void stop() {
                animation_.stop();
            }

            void handleEvent(Event* pEvent);

            // used to build aabb
            const Vector3 getMin() const {
                return animation_.getMin();
            }
            // used to build aabb
            const Vector3 getMax() const {
                return animation_.getMax();
            }
    };

}

#endif // SPRITE_ANIMATION_COMPONENT_H_
