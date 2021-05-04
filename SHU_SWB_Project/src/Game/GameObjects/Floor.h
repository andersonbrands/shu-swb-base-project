/***************************************************************************************
*	Title: Floor.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef FLOOR_H_
#define FLOOR_H_

#include "../../Framework/GameObjects/GameObject.h"

using namespace Framework;

class Floor : public GameObject {
    private:
    public:
        Floor();
        virtual ~Floor();

        virtual void setup();
        virtual void update();
};

#endif // FLOOR_H_
