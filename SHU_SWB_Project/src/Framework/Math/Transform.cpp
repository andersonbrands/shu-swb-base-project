/***************************************************************************************
*	Title: Transform.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
*	Based on original by Bruce Sutherland available at http://www.apress.com/9781430258308 (2014)
*
***************************************************************************************/

#include "Transform.h"
#include <cassert>

namespace Framework {

    Transform::Transform() : translation_(0.0f), scale_(1.0f), rotation_(0.0f), matrix_() {

    }

    Transform::~Transform() {
    }

    void Transform::clone(const Transform& transform) {
        rotation_ = transform.rotation_;
        translation_ = transform.translation_;
        scale_ = transform.scale_;
    }

    void Transform::rotate(const Vector3& rotation) {
        rotation_ = rotation_ + rotation;
    }
    void Transform::scale(const Vector3& scale) {
        scale_ = scale_ * scale;
    }
    void Transform::translate(const Vector3& translation) {
        translation_ = translation_ + translation;
    }

    void Transform::setRotation(const Vector3& rotation) {
        rotation_ = rotation;
    }

    const Vector3& Transform::getRotation() const {
        return rotation_;
    }

    void Transform::setTranslation(const Vector3& translation) {
        translation_ = translation;
    }

    const Vector3& Transform::getTranslation() const {
        return translation_;
    }

    void Transform::setScale(const Vector3& scale) {
        scale_ = scale;
    }

    const Vector3& Transform::getScale() const {
        return scale_;
    }

    void Transform::applyRotation() {
        float x(rotation_.getX()), y(rotation_.getY()), z(rotation_.getZ());

        if(x != 0.0f) {
            float xSin(sin(x)), xCos(cos(x));

            Matrix4 rotX(Vector3(1, 0, 0),Vector3(0, xCos, xSin),Vector3(0, -xSin, xCos),Vector3());

            matrix_ *= rotX;
        }
        if(y != 0.0f) {
            float ySin(sin(y)), yCos(cos(y));

            Matrix4 rotY(Vector3(yCos, 0, -ySin),Vector3(0, 1, 0),Vector3(ySin, 0, yCos),Vector3());

            matrix_ *= rotY;
        }
        if(z != 0.0f) {
            float zSin(sin(z)), zCos(cos(z));

            Matrix4 rotZ(Vector3(zCos, zSin, 0),Vector3(-zSin, zCos, 0),Vector3(0, 0, 1),Vector3());

            matrix_ *= rotZ;
        }
    }
    void Transform::applyScale() {
        assert(scale_.getX() != 0.0f && scale_.getY() != 0.0f && scale_.getZ() != 0.0f);

        Matrix4 scaleMat(Vector3(scale_.getX(), 0, 0),Vector3(0, scale_.getY(), 0),Vector3(0, 0, scale_.getZ()),Vector3());

        matrix_ *= scaleMat;
    }
    void Transform::applyTranslation() {
        if (translation_.getX() == 0 && translation_.getY() == 0 && translation_.getZ() == 0)
            return;

        Matrix4 translationMat(Vector3(1, 0, 0),Vector3(0, 1, 0),Vector3(0, 0, 1),translation_);

        matrix_ *= translationMat;
    }

    void Transform::setMatrix() {
        matrix_.identify();
        applyTranslation();
        applyRotation();
        applyScale();
    }

    const Matrix4 Transform::getMatrix() const {
        return matrix_;
    }

}
