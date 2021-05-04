/***************************************************************************************
*	Title: Frustum.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef FRUSTUM_H_
#define FRUSTUM_H_

#include "../Math/Plane.h"


namespace Framework {

    class Frustum {
        public:
            enum FrustumParameters {
                NEAR,
                FAR,
                TOP,
                BOTTOM,
                RIGHT,
                LEFT,
                NUM_PARAMS
            };

        private:
            Plane planes_[NUM_PARAMS];
        public:
            Frustum() { }
            virtual ~Frustum() { }

            void setPlane(FrustumParameters planeIndex, const Vector3& point, const Vector3& normal) {
                planes_[planeIndex].setup(point, normal);
            }
            const Plane getPlane(FrustumParameters planeIndex) const {
                return planes_[planeIndex];
            }
            bool isInside(const Vector3& point, float radius) const {
                for (int i(0); i < NUM_PARAMS; i++) {
                    if (!planes_[i].isInFront(point, radius))
                        return false;
                }

                return true;
            }
    };

}

#endif // FRUSTUM_H_
