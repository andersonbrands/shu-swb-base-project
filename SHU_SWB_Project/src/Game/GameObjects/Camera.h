/***************************************************************************************
*	Title: Camera.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef CAMERA_H_
#define CAMERA_H_

#include "../../Framework/GameObjects/GameObject.h"
#include "MouseIndicator.h"
#include "../../Framework/Math/Vector3.h"

using namespace Framework;

class Camera : public GameObject {
    private:
        MouseIndicator mIndicator_;
        Vector3 mouseVec_;
    public:
        Camera();
        virtual ~Camera();

        GameObject* getMouseIndicatorPtr() {
            return &mIndicator_;
        }

        virtual void setup();

        virtual void update();
};

#endif // CAMERA_H_
