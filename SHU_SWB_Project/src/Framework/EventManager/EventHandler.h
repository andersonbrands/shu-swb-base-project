/***************************************************************************************
*	Title: EventHandler.h
*	Author: Brandao, Anderson
*	Date: 2014
*
*	Based on original by Bruce Sutherland available at http://www.apress.com/9781430258308 (2014)
*
***************************************************************************************/

#ifndef EVENT_HANDLER_H_
#define EVENT_HANDLER_H_

namespace Framework {
    class Event;

    class EventHandler {
        public:
            virtual ~EventHandler()	{}

            virtual void handleEvent(Event* pEvent) = 0;
    };
}

#endif // EVENT_HANDLER_H_
