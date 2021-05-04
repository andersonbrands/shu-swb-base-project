/***************************************************************************************
*	Title: Plane.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
*	Based on original by Bruce Sutherland available at http://www.apress.com/9781430258308 (2014)
*
***************************************************************************************/

#include "Plane.h"


namespace Framework {
    Plane::Plane() : dot_(0.0f) {

    }

    Plane::Plane(const Vector3& point, const Vector3& normal) {
        setup(point, normal);
    }

    Plane::~Plane() {

    }

    void Plane::setup(const Vector3& point, const Vector3& normal) {
        normal_ = normal_;
        normal_.normalise();

        dot_ = normal_.dot(point);
    }

    bool Plane::isInFront(const Vector3& point, float radius/* = 0.0f */) const {
        return normal_.dot(point) >= (dot_ - radius);
    }

}
