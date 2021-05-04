/***************************************************************************************
*	Title: MouseIndicator.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef MOUSE_INDICATOR_H_
#define MOUSE_INDICATOR_H_

#include "../../Framework/GameObjects/GameObject.h"

using namespace Framework;

class MouseIndicator : public GameObject {
    private:
    public:
        MouseIndicator();
        virtual ~MouseIndicator();

        virtual void setup();
        virtual void update();
};

#endif // MOUSE_INDICATOR_H_
