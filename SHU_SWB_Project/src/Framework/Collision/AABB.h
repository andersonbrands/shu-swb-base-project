/***************************************************************************************
*	Title: AABB.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef AABB_H_
#define AABB_H_

#include "../Math/Vector3.h"

namespace Framework {
    class AABB {
        private:
            Vector3 max_;
            Vector3 min_;
        public:
            AABB();
            ~AABB();

            bool collides(const AABB&) const;

            void setMin(const Vector3& min) {
                min_ = min;
            }

            const Vector3 getMin() {
                return min_;
            }

            void setMax(const Vector3& max) {
                max_ = max;
            }

            const Vector3 getMax() {
                return max_;
            }
    };

}

#endif // AABB_H_
