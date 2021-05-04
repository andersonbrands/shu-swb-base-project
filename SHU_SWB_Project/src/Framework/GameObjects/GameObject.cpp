/***************************************************************************************
*	Title: GameObject.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
*	Based on original by Bruce Sutherland available at http://www.apress.com/9781430258308 (2014)
*
***************************************************************************************/

#include "GameObject.h"

namespace Framework {
    GameObject::GameObject() {

    }

    GameObject::~GameObject() {
        for (ComponentUnorderedMapIterator iter = components_.begin(); iter != components_.end(); ++iter) {
            Component* pComponent = iter->second;
            if (pComponent) {
                delete pComponent;
                pComponent = nullptr;
            }
        }
    }

    Component* GameObject::getComponent(unsigned int id) {
        ComponentUnorderedMapIterator result = components_.find(id);
        return result == components_.end() ? nullptr : result->second;
    }

    void GameObject::setup() {

    }
    void GameObject::update() {

    }
}
