/***************************************************************************************
*	Title: EventManager.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
*	Based on original by Bruce Sutherland available at http://www.apress.com/9781430258308 (2014)
*
***************************************************************************************/

#include "EventManager.h"

namespace Framework {
    EventManager::EventManager() {

    }

    EventManager::~EventManager() {
        for (EventMapIterator iter = eventMap_.begin(); iter != eventMap_.end(); ++iter) {
            Event* pEvent = iter->second;
            if (pEvent) {
                delete pEvent;
                iter->second = NULL;
            }
        }

        eventMap_.clear();
    }

    void EventManager::sendEvent(EventId eventId, void* pData) {
        EventMapIterator result = eventMap_.find(eventId);
        if (result != eventMap_.end()) {
            assert(result->second);
            if (result->second) {
                result->second->send(pData);
            }
        }
    }

    void EventManager::sendEventToHandler(EventId eventId, EventHandler& eventHandler, void* pData) {
        EventMapIterator result = eventMap_.find(eventId);
        if (result != eventMap_.end()) {
            assert(result->second);
            if (result->second) {
                result->second->sendToHandler(eventHandler, pData);
            }
        }
    }

    bool EventManager::registerEvent(EventId eventId) {
        bool added = false;

        EventMapIterator result = eventMap_.find(eventId);
        if (result == eventMap_.end()) {
            Event* pNewEvent = new Event(eventId);

            if (pNewEvent) {
                std::pair<EventId, Event*> newEvent(eventId, pNewEvent);
                std::pair<EventMapIterator, bool> addedIter = eventMap_.insert(newEvent);
                added = addedIter.second;
            }
        }

        assert(added);
        return added;
    }

    void EventManager::attachEvent(EventId eventId, EventHandler& eventHandler) {
        EventMapIterator result = eventMap_.find(eventId);
        assert(result != eventMap_.end());
        if (result != eventMap_.end()) {
            assert(result->second);
            result->second->attachListener(eventHandler);
        }
    }

    void EventManager::detachEvent(EventId eventId, EventHandler& eventHandler) {
        EventMapIterator result = eventMap_.find(eventId);
        assert(result != eventMap_.end());
        if (result != eventMap_.end()) {
            assert(result->second);
            result->second->detachListener(eventHandler);
        }
    }
}
