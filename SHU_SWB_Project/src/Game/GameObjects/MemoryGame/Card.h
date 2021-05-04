/***************************************************************************************
*	Title: Card.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef CARD_H_
#define CARD_H_

#include "../../../Framework/GameObjects/GameObject.h"
#include "../../../Framework/Renderer/Sprite/Sprite.h"
#include "../../../Framework/EventManager/EventHandler.h"

using namespace Framework;

class Card : public GameObject, EventHandler {
    private:
        bool matched_;
        int id_;
    public:
        Card();
        virtual ~Card();

        int getId() {
            return id_;
        }
        void setId(int id) {
            id_ = id;
        }

        void reset();
        void match();
        bool isMatched() {
            return matched_;
        }
        void flip();
        virtual void setup(Sprite* pSprite);
        void setPosition(const Vector3 &pos);
        virtual void update();

        virtual void handleEvent(Event* pEvent);
};

#endif // CARD_H_
