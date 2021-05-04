/***************************************************************************************
*	Title: CollisionManager.h
*	Author: Brandao, Anderson
*	Date: 2014
*
*	Based on original (CollisionManager.h) by Bruce Sutherland available at http://www.apress.com/9781430258308 (2014)
*
***************************************************************************************/

#ifndef COLLISION_MANAGER_H_
#define COLLISION_MANAGER_H_

#include "../Utilities/Singleton.h"
#include "CollisionGroup.h"

namespace Framework {

    class CollisionManager : public Singleton<CollisionManager> {
        private:
            typedef std::vector<CollisionGroup>	CollisionGroupVector;

            CollisionGroupVector					collisionGroups_;

            void test(GameObject*, GameObject*);

        public:
            CollisionManager();
            virtual ~CollisionManager();

            void addCollisionGroup();
            void addObjectToGroup(const unsigned int groupIndex, GameObject* pObject);
            void testAgainstGroup(const unsigned int groupIndex, GameObject* pObject);
            void clearGroup(const unsigned int groupIndex);

    };

}
#endif // COLLISION_MANAGER_H_
