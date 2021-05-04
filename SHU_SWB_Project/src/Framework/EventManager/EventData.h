/***************************************************************************************
*	Title: EventData.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef EVENT_DATA_H_
#define EVENT_DATA_H_

#include "../Utilities/Utils.h"
#include "../GameObjects/GameObject.h"

namespace Framework {

    struct MovementEventData {
        Direction direction;
    };

    struct CollisionEventData {
        GameObject* go1;
		GameObject* go2;
    };

}

#endif // EVENT_DATA_H_
