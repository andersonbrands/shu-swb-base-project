/***************************************************************************************
*	Title: Component.h
*	Author: Brandao, Anderson
*	Date: 2014
*
*	Based on original by Bruce Sutherland available at http://www.apress.com/9781430258308 (2014)
*
***************************************************************************************/

#ifndef COMPONENT_H_
#define COMPONENT_H_

namespace Framework {
    class GameObject;

    class Component {
        private:
            GameObject* pOwner_;

        public:
            explicit Component(GameObject* pOwner)
                :	pOwner_(pOwner) {
            }

            virtual ~Component()	{}

            GameObject* getOwner() const {
                return pOwner_;
            }
    };
}

#endif // COMPONENT_H_
