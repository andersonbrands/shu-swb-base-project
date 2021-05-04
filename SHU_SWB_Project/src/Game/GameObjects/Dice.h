/***************************************************************************************
*	Title: Dice.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef DICE_H_
#define DICE_H_

#include "../../Framework/GameObjects/GameObject.h"

using namespace Framework;

class Dice : public GameObject {
    private:
    public:
        Dice();
        virtual ~Dice();

        virtual void setup();

        virtual void update();
};

#endif // DICE_H_
