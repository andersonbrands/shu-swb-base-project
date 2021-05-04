/***************************************************************************************
*	Title: CollisionGroup.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*	
*	Based on original (CollisionBin.cpp) by Bruce Sutherland available at http://www.apress.com/9781430258308 (2014)
*
***************************************************************************************/

#include "CollisionGroup.h"

namespace Framework {

    CollisionGroup::CollisionGroup() {

    }

    CollisionGroup::~CollisionGroup() {
        collisionObjects_.clear();
    }

    void CollisionGroup::addObject(GameObject* pGameObject) {
        collisionObjects_.push_back(pGameObject);
    }

    GameObject* CollisionGroup::getFirst() {
        currentObject_ = collisionObjects_.begin();
        return currentObject_ != collisionObjects_.end()
               ?	*currentObject_
               :	NULL;
    }

    GameObject* CollisionGroup::getNext() {
        GameObject* pRet = NULL;

        if (currentObject_ != collisionObjects_.end()) {
            ++currentObject_;
            pRet = currentObject_ != collisionObjects_.end()
                   ?	*currentObject_
                   :	NULL;
        }

        return pRet;
    }

    void CollisionGroup::clear() {
        collisionObjects_.clear();
        currentObject_ = collisionObjects_.begin();
    }
}