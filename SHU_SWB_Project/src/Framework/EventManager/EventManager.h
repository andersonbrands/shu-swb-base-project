/***************************************************************************************
*	Title: EventManager.h
*	Author: Brandao, Anderson
*	Date: 2014
*
*	Based on original by Bruce Sutherland available at http://www.apress.com/9781430258308 (2014)
*
***************************************************************************************/

#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

#include "../Utilities/Singleton.h"
#include <unordered_map>
#include "EventId.h"
#include "Event.h"

#include <cassert>

namespace Framework {
    class EventManager : public Singleton<EventManager> {
            friend void sendEvent(EventId eventId, void* pData = nullptr);
            friend void sendEventToHandler(EventId eventId, EventHandler& eventHandler, void* pData = nullptr);
            friend bool registerEvent(EventId eventId);
            friend void attachEvent(EventId eventId, EventHandler& eventHandler);
            friend void detachEvent(EventId eventId, EventHandler& eventHandler);

        private:
            typedef std::tr1::unordered_map<EventId, Event*>	EventMap;
            typedef EventMap::iterator							EventMapIterator;

            EventMap								eventMap_;

            void sendEvent(EventId eventId, void* pData);
            void sendEventToHandler(EventId eventId, EventHandler& eventHandler, void* pData);
            bool registerEvent(EventId eventId);
            void attachEvent(EventId eventId, EventHandler& eventHandler);
            void detachEvent(EventId eventId, EventHandler& eventHandler);

        public:
            EventManager();
            ~EventManager();
    };

    inline void sendEvent(EventId eventId, void* pData/* = nullptr*/) {
        EventManager* pEventManager = EventManager::getInstancePtr();
        assert(pEventManager);
        if (pEventManager) {
            pEventManager->sendEvent(eventId, pData);
        }
    }

    inline void sendEventToHandler(EventId eventId, EventHandler& eventHandler, void* pData/* = nullptr */) {
        EventManager* pEventManager = EventManager::getInstancePtr();
        assert(pEventManager);
        if (pEventManager) {
            pEventManager->sendEventToHandler(eventId, eventHandler, pData);
        }
    }

    inline bool registerEvent(EventId eventId) {
        EventManager* pEventManager = EventManager::getInstancePtr();
        assert(pEventManager);
        if (pEventManager) {
            pEventManager->registerEvent(eventId);
        }

        return true;
    }

    inline void attachEvent(EventId eventId, EventHandler& eventHandler) {
        EventManager* pEventManager = EventManager::getInstancePtr();
        assert(pEventManager);
        if (pEventManager) {
            pEventManager->attachEvent(eventId, eventHandler);
        }
    }

    inline void detachEvent(EventId eventId, EventHandler& eventHandler) {
        EventManager* pEventManager = EventManager::getInstancePtr();
        assert(pEventManager);
        if (pEventManager) {
            pEventManager->detachEvent(eventId, eventHandler);
        }
    }
}

#endif // EVENTMANAGER_H_
