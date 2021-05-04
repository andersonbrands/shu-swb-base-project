/***************************************************************************************
*	Title: Transform.h
*	Author: Brandao, Anderson
*	Date: 2014
*
*	Based on original by Bruce Sutherland available at http://www.apress.com/9781430258308 (2014)
*
***************************************************************************************/

#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "Vector3.h"
#include "Matrix4.h"
#include <math.h>

namespace Framework {

    class Transform {
        private:
            Vector3 rotation_;
            Vector3 translation_;
            Vector3 scale_;
            Matrix4 matrix_;

            void applyRotation();
            void applyScale();
            void applyTranslation();
        public:
            Transform();
            virtual ~Transform();

            void clone(const Transform& transform);

            void rotate(const Vector3& rotation);
            void scale(const Vector3& rotation);
            void translate(const Vector3& rotation);

            void setRotation(const Vector3& rotation);
            const Vector3& getRotation() const;

            void setTranslation(const Vector3& translation);
            const Vector3& getTranslation() const;

            void setScale(const Vector3& scale);
            const Vector3& getScale() const;

			void setMatrix();
            const Matrix4 getMatrix() const;
    };

}
#endif // TRANSFORM_H_ 
