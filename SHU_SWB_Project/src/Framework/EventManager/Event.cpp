/***************************************************************************************
*	Title: Event.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
*	Based on original by Bruce Sutherland available at http://www.apress.com/9781430258308 (2014)
*
***************************************************************************************/

#include "Event.h"
#include <cassert>

namespace Framework {
    Event::Event(EventId eventId)
        :	id_(eventId) {
    }

    Event::~Event() {
        listeners_.clear();
    }

    void Event::send(void* pData) {
        pData_ = pData;
        for (EventHandlerListIterator iter = listeners_.begin(); iter != listeners_.end(); ++iter) {
            EventHandler* pEventHandler = *iter;
            assert(pEventHandler);
            if (pEventHandler) {
                pEventHandler->handleEvent(this);
            }
        }
    }

    void Event::sendToHandler(EventHandler& eventHandler, void* pData) {
        pData_ = pData;
        for (EventHandlerListIterator iter = listeners_.begin(); iter != listeners_.end(); ++iter) {
            if (&eventHandler == *iter) {
                eventHandler.handleEvent(this);
            }
        }
    }

    void Event::attachListener(EventHandler& eventHandler) {
        listeners_.push_back(&eventHandler);
    }

    void Event::detachListener(EventHandler& eventHandler) {
        for (EventHandlerListIterator iter = listeners_.begin(); iter != listeners_.end(); ++iter) {
            if (&eventHandler == *iter) {
                listeners_.erase(iter);
                break;
            }
        }
    }
}
