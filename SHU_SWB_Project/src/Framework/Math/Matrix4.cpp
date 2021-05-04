/***************************************************************************************
*	Title: Matrix4.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
*	Based on original by Bruce Sutherland available at http://www.apress.com/9781430258308 (2014)
*
***************************************************************************************/

#include "Matrix4.h"

namespace Framework {

    Matrix4::Matrix4() {
        identify();
    }

    Matrix4::Matrix4(const Vector3& col1,const Vector3& col2,const Vector3& col3,const Vector3& col4) {
        m_[0] = col1.getX();
        m_[1] = col2.getX();
        m_[2] = col3.getX();
        m_[3] = col4.getX();

        m_[4] = col1.getY();
        m_[5] = col2.getY();
        m_[6] = col3.getY();
        m_[7] = col4.getY();

        m_[8] = col1.getZ();
        m_[9] = col2.getZ();
        m_[10] = col3.getZ();
        m_[11] = col4.getZ();

        m_[12] = 0.0f;
        m_[13] = 0.0f;
        m_[14] = 0.0f;
        m_[15] = 1.0f;
    }

    Matrix4::~Matrix4() {

    }

    void Matrix4::identify() {
        m_[0] = 1.0f;
        m_[1] = 0.0f;
        m_[2] = 0.0f;
        m_[3] = 0.0f;

        m_[4] = 0.0f;
        m_[5] = 1.0f;
        m_[6] = 0.0f;
        m_[7] = 0.0f;

        m_[8] = 0.0f;
        m_[9] = 0.0f;
        m_[10] = 1.0f;
        m_[11] = 0.0f;

        m_[12] = 0.0f;
        m_[13] = 0.0f;
        m_[14] = 0.0f;
        m_[15] = 1.0f;
    }

    // operators
    Matrix4 Matrix4::operator *( const Matrix4& rhs ) const {
        Matrix4 result;

        result.m_[0] = (m_[0] * rhs.m_[0]) + (m_[1] * rhs.m_[4]) + (m_[2] * rhs.m_[8]) + (m_[3] * rhs.m_[12]);
        result.m_[1] = (m_[0] * rhs.m_[1]) + (m_[1] * rhs.m_[5]) + (m_[2] * rhs.m_[9]) + (m_[3] * rhs.m_[13]);
        result.m_[2] = (m_[0] * rhs.m_[2]) + (m_[1] * rhs.m_[6]) + (m_[2] * rhs.m_[10]) + (m_[3] * rhs.m_[14]);
        result.m_[3] = (m_[0] * rhs.m_[3]) + (m_[1] * rhs.m_[7]) + (m_[2] * rhs.m_[11]) + (m_[3] * rhs.m_[15]);

        result.m_[4] = (m_[4] * rhs.m_[0]) + (m_[5] * rhs.m_[4]) + (m_[6] * rhs.m_[8]) + (m_[7] * rhs.m_[12]);
        result.m_[5] = (m_[4] * rhs.m_[1]) + (m_[5] * rhs.m_[5]) + (m_[6] * rhs.m_[9]) + (m_[7] * rhs.m_[13]);
        result.m_[6] = (m_[4] * rhs.m_[2]) + (m_[5] * rhs.m_[6]) + (m_[6] * rhs.m_[10]) + (m_[7] * rhs.m_[14]);
        result.m_[7] = (m_[4] * rhs.m_[3]) + (m_[5] * rhs.m_[7]) + (m_[6] * rhs.m_[11]) + (m_[7] * rhs.m_[15]);

        result.m_[8] = (m_[8] * rhs.m_[0]) + (m_[9] * rhs.m_[4]) + (m_[10] * rhs.m_[8]) + (m_[11] * rhs.m_[12]);
        result.m_[9] = (m_[8] * rhs.m_[1]) + (m_[9] * rhs.m_[5]) + (m_[10] * rhs.m_[9]) + (m_[11] * rhs.m_[13]);
        result.m_[10] = (m_[8] * rhs.m_[2]) + (m_[9] * rhs.m_[6]) + (m_[10] * rhs.m_[10]) + (m_[11] * rhs.m_[14]);
        result.m_[11] = (m_[8] * rhs.m_[3]) + (m_[9] * rhs.m_[7]) + (m_[10] * rhs.m_[11]) + (m_[11] * rhs.m_[15]);

        result.m_[12] = (m_[12] * rhs.m_[0]) + (m_[13] * rhs.m_[4]) + (m_[14] * rhs.m_[8]) + (m_[15] * rhs.m_[12]);
        result.m_[13] = (m_[12] * rhs.m_[1]) + (m_[13] * rhs.m_[5]) + (m_[14] * rhs.m_[9]) + (m_[15] * rhs.m_[13]);
        result.m_[14] = (m_[12] * rhs.m_[2]) + (m_[13] * rhs.m_[6]) + (m_[14] * rhs.m_[10]) + (m_[15] * rhs.m_[14]);
        result.m_[15] = (m_[12] * rhs.m_[3]) + (m_[13] * rhs.m_[7]) + (m_[14] * rhs.m_[11]) + (m_[15] * rhs.m_[15]);

        return result;
    }
    Vector3 Matrix4::operator *( const Vector3& rhs ) const {
        Vector3 result;

        result.setX(m_[0] * rhs.getX() + m_[1] * rhs.getY() + m_[2] * rhs.getZ() + m_[3]);

        result.setY(m_[4] * rhs.getX() + m_[5] * rhs.getY() + m_[6] * rhs.getZ() + m_[7]);

        result.setZ(m_[8] * rhs.getX() + m_[9] * rhs.getY() + m_[10] * rhs.getZ() + m_[11]);

        return result;
    }
    Matrix4& Matrix4::operator *=( const Matrix4& rhs ) {
        Matrix4 copy(*this);

        m_[0] = (copy.m_[0] * rhs.m_[0]) + (copy.m_[1] * rhs.m_[4]) + (copy.m_[2] * rhs.m_[8]) + (copy.m_[3] * rhs.m_[12]);
        m_[1] = (copy.m_[0] * rhs.m_[1]) + (copy.m_[1] * rhs.m_[5]) + (copy.m_[2] * rhs.m_[9]) + (copy.m_[3] * rhs.m_[13]);
        m_[2] = (copy.m_[0] * rhs.m_[2]) + (copy.m_[1] * rhs.m_[6]) + (copy.m_[2] * rhs.m_[10]) + (copy.m_[3] * rhs.m_[14]);
        m_[3] = (copy.m_[0] * rhs.m_[3]) + (copy.m_[1] * rhs.m_[7]) + (copy.m_[2] * rhs.m_[11]) + (copy.m_[3] * rhs.m_[15]);

        m_[4] = (copy.m_[4] * rhs.m_[0]) + (copy.m_[5] * rhs.m_[4]) + (copy.m_[6] * rhs.m_[8]) + (copy.m_[7] * rhs.m_[12]);
        m_[5] = (copy.m_[4] * rhs.m_[1]) + (copy.m_[5] * rhs.m_[5]) + (copy.m_[6] * rhs.m_[9]) + (copy.m_[7] * rhs.m_[13]);
        m_[6] = (copy.m_[4] * rhs.m_[2]) + (copy.m_[5] * rhs.m_[6]) + (copy.m_[6] * rhs.m_[10]) + (copy.m_[7] * rhs.m_[14]);
        m_[7] = (copy.m_[4] * rhs.m_[3]) + (copy.m_[5] * rhs.m_[7]) + (copy.m_[6] * rhs.m_[11]) + (copy.m_[7] * rhs.m_[15]);

        m_[8] = (copy.m_[8] * rhs.m_[0]) + (copy.m_[9] * rhs.m_[4]) + (copy.m_[10] * rhs.m_[8]) + (copy.m_[11] * rhs.m_[12]);
        m_[9] = (copy.m_[8] * rhs.m_[1]) + (copy.m_[9] * rhs.m_[5]) + (copy.m_[10] * rhs.m_[9]) + (copy.m_[11] * rhs.m_[13]);
        m_[10] = (copy.m_[8] * rhs.m_[2]) + (copy.m_[9] * rhs.m_[6]) + (copy.m_[10] * rhs.m_[10]) + (copy.m_[11] * rhs.m_[14]);
        m_[11] = (copy.m_[8] * rhs.m_[3]) + (copy.m_[9] * rhs.m_[7]) + (copy.m_[10] * rhs.m_[11]) + (copy.m_[11] * rhs.m_[15]);

        m_[12] = (copy.m_[12] * rhs.m_[0]) + (copy.m_[13] * rhs.m_[4]) + (copy.m_[14] * rhs.m_[8]) + (copy.m_[15] * rhs.m_[12]);
        m_[13] = (copy.m_[12] * rhs.m_[1]) + (copy.m_[13] * rhs.m_[5]) + (copy.m_[14] * rhs.m_[9]) + (copy.m_[15] * rhs.m_[13]);
        m_[14] = (copy.m_[12] * rhs.m_[2]) + (copy.m_[13] * rhs.m_[6]) + (copy.m_[14] * rhs.m_[10]) + (copy.m_[15] * rhs.m_[14]);
        m_[15] = (copy.m_[12] * rhs.m_[3]) + (copy.m_[13] * rhs.m_[7]) + (copy.m_[14] * rhs.m_[11]) + (copy.m_[15] * rhs.m_[15]);

        return *this;
    }

}



