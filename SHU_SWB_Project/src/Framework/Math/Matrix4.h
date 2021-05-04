/***************************************************************************************
*	Title: Matrix4.h
*	Author: Brandao, Anderson
*	Date: 2014
*
*	Based on original by Bruce Sutherland available at http://www.apress.com/9781430258308 (2014)
*
***************************************************************************************/

#ifndef MATRIX_4_H_
#define MATRIX_4_H_

#include <cassert>
#include "Vector3.h"

namespace Framework {

    class Matrix4 {
        private:
            float m_[16];
        public:

            Matrix4();
            Matrix4(const Vector3& col1,const Vector3& col2,const Vector3& col3,const Vector3& col4);
            ~Matrix4();

            void identify();

            float get(int index) const {
                return m_[index];
            }

            // operators
            Matrix4 operator *( const Matrix4& rhs ) const;
            Vector3 operator *( const Vector3& rhs ) const;
            Matrix4& operator *=( const Matrix4& rhs );
    };
}

#endif // MATRIX_4_H_
