/***************************************************************************************
*	Title: SpriteExplosion.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef SPRITE_EXPLOSION_H_
#define SPRITE_EXPLOSION_H_

#include "../../Framework/GameObjects/GameObject.h"

using namespace Framework;

class SpriteExplosion : public GameObject {
    private:
    public:
        SpriteExplosion();
        virtual ~SpriteExplosion();

        virtual void setup();
        virtual void update();
};

#endif // SPRITE_EXPLOSION_H_
