/***************************************************************************************
*	Title: EventId.h
*	Author: Brandao, Anderson
*	Date: 2014
*
*	Based on original by Bruce Sutherland available at http://www.apress.com/9781430258308 (2014)
*
***************************************************************************************/

#ifndef EVENT_ID_H_
#define EVENT_ID_H_

namespace Framework {
    typedef unsigned int EventId;

    //static const EventId EVENT_NAME	= value;
    static const EventId ON_LOST_DEVICE = 0;
    static const EventId ON_RESET_DEVICE = 1;
    static const EventId CHECK_DEVICE_IS_LOST = 2;
    static const EventId TOGGLE_FULLSCREEN = 3;
    static const EventId PLATFORM_SUSPEND = 4;
    static const EventId PLATFORM_RESUME = 5;
    static const EventId PLATFORM_STOP = 6;
    static const EventId PRE_RENDER_EVENT = 7;
    static const EventId RENDER_EVENT = 8;
    static const EventId CAMERA_MOVE = 9;
    static const EventId UPDATE = 10;
    static const EventId POST_UPDATE = 11;
    static const EventId COLLISION_EVENT = 12;
    static const EventId CLICKED_CARD = 13;
    static const EventId APP_QUIT = 14;

    // TODO: create game specific events outside framework
}

#endif // EVENT_ID_H_
