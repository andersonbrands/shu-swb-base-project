/***************************************************************************************
*	Title: Event.h
*	Author: Brandao, Anderson
*	Date: 2014
*
*	Based on original by Bruce Sutherland available at http://www.apress.com/9781430258308 (2014)
*
***************************************************************************************/

#ifndef EVENT_H_
#define EVENT_H_

#include <vector>
#include "EventHandler.h"
#include "EventId.h"

namespace Framework {
    class Event {
        private:
            typedef std::vector<EventHandler*>		EventHandlerList;
            typedef EventHandlerList::iterator		EventHandlerListIterator;

            EventHandlerList	listeners_;
            EventId				id_;
            void*				pData_;
        public:
            explicit Event(EventId eventId);
            ~Event();

            void send(void* pData);
            void sendToHandler(EventHandler& eventHandler, void* pData);
            void attachListener(EventHandler& eventHandler);
            void detachListener(EventHandler& eventHandler);

            EventId getID()	const {
                return id_;
            }
            void* getData() {
                return pData_;
            }
    };
}

#endif // EVENT_H_
