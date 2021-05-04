/***************************************************************************************
*	Title: AABB.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#include "AABB.h"

namespace Framework {

    AABB::AABB() {

    }
    AABB::~AABB() {

    }

    bool AABB::collides(const AABB& bb) const {
        bool collides(true);

        if (	min_.getX() > bb.max_.getX() ||
                min_.getY() > bb.max_.getY() ||
                min_.getZ() > bb.max_.getZ() ||

                max_.getX() < bb.min_.getX() ||
                max_.getY() < bb.min_.getY() ||
                max_.getZ() < bb.min_.getZ() ) {

            collides = false;

        }

        return collides;
    }

}

