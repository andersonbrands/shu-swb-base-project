/***************************************************************************************
*	Title: GameObject.h
*	Author: Brandao, Anderson
*	Date: 2014
*
*	Based on original by Bruce Sutherland available at http://www.apress.com/9781430258308 (2014)
*
***************************************************************************************/

#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <unordered_map>
#include "Component.h"
#include "ComponentId.h"

namespace Framework {
    class GameObject {
            template <class T>
            friend T* component_cast(GameObject& object);

            template <class T>
            friend T* component_cast(GameObject* pObject);

        private:
            typedef std::tr1::unordered_map<ComponentId, Component*>	ComponentUnorderedMap;
            typedef ComponentUnorderedMap::iterator						ComponentUnorderedMapIterator;
            ComponentUnorderedMap	components_;

            template <class T>
            T*	getComponent() {
                return static_cast<T*>(getComponent(T::getId()));
            }

            Component*	getComponent(ComponentId id);

        public:
            GameObject();
            virtual ~GameObject();

            template <class T>
            bool addComponent();

			virtual void setup();
            virtual void update();
    };

    template <class T>
    T* component_cast(GameObject& object) {
        return object.getComponent<T>();
    }

    template <class T>
    T* component_cast(GameObject* pObject) {
        T* pComponent = nullptr;
        if (pObject) {
            pComponent = pObject->getComponent<T>();
        }

        return pComponent;
    }

    template <class T>
    bool GameObject::addComponent() {
        bool added = false;

        ComponentUnorderedMapIterator result = components_.find(T::getId());
        if (result == components_.end()) {
            T* pNewComponent = new T(this);

            if (pNewComponent) {
                std::pair<ComponentId, Component*> newComponent(T::getId(), pNewComponent);
                std::pair<ComponentUnorderedMapIterator, bool> addedIter = components_.insert(newComponent);
                added = addedIter.second;
            }
        }
        return added;
    }
}

#endif // GAME_OBJECT_H_
