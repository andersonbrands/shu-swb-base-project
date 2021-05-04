/***************************************************************************************
*	Title: CollisionManager.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
*	Based on original (CollisionManager.cpp) by Bruce Sutherland available at http://www.apress.com/9781430258308 (2014)
*
***************************************************************************************/

#include "CollisionManager.h"
#include "../GameObjects/Components/AABBColliderComponent.h"
#include "../EventManager/EventManager.h"
#include "../EventManager/EventData.h"
#include <cassert>

namespace Framework {

    CollisionManager::CollisionManager() {
        registerEvent(COLLISION_EVENT);
    }

    CollisionManager::~CollisionManager() {

    }

    void CollisionManager::addCollisionGroup() {
        collisionGroups_.push_back(CollisionGroup());
    }

    void CollisionManager::addObjectToGroup(const unsigned int binIndex, GameObject* pObject) {
        assert(binIndex < collisionGroups_.size());
        collisionGroups_[binIndex].addObject(pObject);
    }

    void CollisionManager::testAgainstGroup(const unsigned int binIndex, GameObject* pObject) {
        assert(binIndex < collisionGroups_.size());
        CollisionGroup& bin = collisionGroups_[binIndex];
        GameObject* pGroupObject = bin.getFirst();
        while (pGroupObject) {

            test(pObject, pGroupObject);

            pGroupObject = bin.getNext();
        }
    }

    void CollisionManager::test(GameObject* go1, GameObject* go2) {
        if (go1 == go2) return;

        AABBColliderComponent* pAabbComp1 = component_cast<AABBColliderComponent>(go1);
        AABBColliderComponent* pAabbComp2 = component_cast<AABBColliderComponent>(go2);

        assert (pAabbComp1 && pAabbComp2);

        if (pAabbComp1->collides(pAabbComp2)) {
            CollisionEventData collisionData;
            collisionData.go1 = go1;
            collisionData.go2 = go2;

            sendEvent(COLLISION_EVENT, &collisionData);
        }
    }

    void CollisionManager::clearGroup(const unsigned int binIndex) {
        assert(binIndex < collisionGroups_.size());
        CollisionGroup& bin = collisionGroups_[binIndex];
        bin.clear();
    }

}