/***************************************************************************************
*	Title: SpriteManager.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef SPRITE_MANAGER_H_
#define SPRITE_MANAGER_H_

#include "../../Utilities/UnorderedMapContainer.h"
#include "../../Utilities/Singleton.h"
#include "SpriteId.h"
#include "Sprite.h"

namespace Framework {

    class SpriteManager : UnorderedMapContainer<SpriteId, Sprite>, public Singleton<SpriteManager> {
        private:
        public:
            SpriteManager();
            virtual ~SpriteManager();

            template <class T>
            T* addSprite(const SpriteId &id) {
                return add<T>(id);
            }

            Sprite* getSprite(const SpriteId &id) {
                return getObject(id);
            }
    };

}

#endif // SPRITE_MANAGER_H_
