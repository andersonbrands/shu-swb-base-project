/***************************************************************************************
*	Title: Plane.h
*	Author: Brandao, Anderson
*	Date: 2014
*
*	Based on original by Bruce Sutherland available at http://www.apress.com/9781430258308 (2014)
*
***************************************************************************************/

#ifndef PLANE_H_
#define PLANE_H_

#include "Vector3.h"

namespace Framework {

    class Plane {
        private:
            float dot_;
            Vector3 normal_;
        public:
            Plane();
            Plane(const Vector3& point, const Vector3& normal);
            virtual ~Plane();

            void setup(const Vector3& point, const Vector3& normal);

            bool isInFront(const Vector3& point, float radius = 0.0f) const;
    };

}

#endif // PLANE_H_
