/***************************************************************************************
*	Title: CollisionGroup.h
*	Author: Brandao, Anderson
*	Date: 2014
*
*	Based on original (CollisionBin.h) by Bruce Sutherland available at http://www.apress.com/9781430258308 (2014)
*
***************************************************************************************/

#ifndef COLLISION_GROUP_H_
#define COLLISION_GROUP_H_

#include <vector>
#include "../GameObjects/GameObject.h"

namespace Framework {

    class CollisionGroup {
        private:
            typedef std::vector<GameObject*>	GameObjectVector;
            typedef GameObjectVector::iterator	GameObjectVectorIterator;

            GameObjectVector					collisionObjects_;
            GameObjectVectorIterator			currentObject_;
        public:
            CollisionGroup();
            ~CollisionGroup();

            void 			addObject(GameObject* pGameObject);
            GameObject*		getFirst();
            GameObject*		getNext();
            void			clear();
    };

}
#endif // COLLISION_GROUP_H_
