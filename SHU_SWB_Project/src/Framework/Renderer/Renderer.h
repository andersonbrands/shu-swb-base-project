/***************************************************************************************
*	Title: Renderer.h
*	Author: Brandao, Anderson
*	Date: 2014
*
*	Based on original by Bruce Sutherland available at http://www.apress.com/9781430258308 (2014)
*
***************************************************************************************/

#ifndef RENDERER_H_
#define RENDERER_H_

#include "../Kernel/Task.h"
#include <vector>
#include <cassert>
#include "../Math/Vector3.h"
#include "../Math/Matrix4.h"
#include "../Utilities/Color.h"

namespace Framework {

    class Renderer : public Task {
        private:
            static Renderer* instance_;
        public:
            explicit Renderer(const unsigned int priority);
            virtual ~Renderer();

            static Renderer* getPtr() {
                return instance_;
            }

            virtual void Renderer::setTransform(const Matrix4& matrix) = 0;
            virtual void Renderer::setTransform(const Vector3& pos, const Vector3& scale, const Vector3& rotation) = 0;
            virtual void Renderer::setupViewMatrices(const Vector3& camPos, const Vector3& camTarget, const Vector3& upVector = Vector3(0.0f, 0.1f, 0.0f)) = 0;

            virtual void drawLine(const Vector3& from, const Vector3& to, const ColorARGB& color = ColorARGB(1.0f, 1.0f, 1.0f, 1.0f)) = 0;
            virtual void drawAABB(const Vector3& min, const Vector3& max, const ColorARGB& color) = 0;

            virtual bool start() = 0;
            virtual void onSuspend() = 0;
            virtual void update() = 0;
            virtual void onResume() = 0;
            virtual void stop() = 0;

    };
}

#endif // RENDERER_H_
