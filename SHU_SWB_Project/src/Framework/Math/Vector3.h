/***************************************************************************************
*	Title: Vector3.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef VECTOR3_H_
#define VECTOR3_H_

#include <cmath>

namespace Framework {

    class Vector3 {
        private:
            float x_;
            float y_;
            float z_;

        public:
            Vector3();
            Vector3(const float x, const float y, const float z);
            Vector3(const float value);

            virtual ~Vector3();

            Vector3& operator=(const Vector3& in);

            // getters
            float getX() const;
            float getY() const;
            float getZ() const;

            // setters
            void setX(const float x );
            void setY(const float y );
            void setZ(const float z );

            // operators
            Vector3 operator +( const Vector3& rhs ) const;
            Vector3 operator -( const Vector3& rhs ) const;
            Vector3 operator *( const Vector3& rhs ) const;
            Vector3 operator /( const Vector3& rhs ) const;

            Vector3 operator +( const float scalar ) const;
            Vector3 operator -( const float scalar ) const;
            Vector3 operator *( const float scalar ) const;
            Vector3 operator /( const float scalar ) const;

            Vector3& operator +=( const Vector3& rhs );
            Vector3& operator -=( const Vector3& rhs );
            Vector3& operator *=( const Vector3& rhs );
            Vector3& operator /=( const Vector3& rhs );

            Vector3& operator +=( const float scalar );
            Vector3& operator -=( const float scalar );
            Vector3& operator *=( const float scalar );
            Vector3& operator /=( const float scalar );

            Vector3 operator -() const;

            // vector operations
            Vector3 cross( const Vector3& rhs) const;
            float dot(const Vector3& rhs) const;
            float lengthSquared() const;
            float length() const;
            void normalise();
    };

}

#endif // VECTOR3_H_
