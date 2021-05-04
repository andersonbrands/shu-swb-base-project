/***************************************************************************************
*	Title: PointLight.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef POINT_LIGHT_H_
#define POINT_LIGHT_H_

#include "../../Framework/GameObjects/GameObject.h"

using namespace Framework;

class PointLight : public GameObject {
    private:
    public:
        PointLight();
        virtual ~PointLight();

        virtual void setup();
        virtual void update();
};

#endif // POINT_LIGHT_H_
