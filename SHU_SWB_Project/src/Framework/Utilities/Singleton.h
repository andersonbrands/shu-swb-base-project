/***************************************************************************************
*	Title: Singleton.h
*	Author: Brandao, Anderson
*	Date: 2014
*
*	Based on original by Bruce Sutherland available at http://www.apress.com/9781430258308 (2014)
*
***************************************************************************************/

#ifndef SINGLETON_H_
#define SINGLETON_H_

#include <cassert>

namespace Framework {
    template <typename T>
    class Singleton {
        private:
            static T*	instance;

        public:
            Singleton() {
                assert(!instance);
                instance = static_cast<T*>(this);
            }

            ~Singleton() {
                assert(instance);
                instance = 0;
            }

            static T& getInstance()		{
                return *instance;
            }
            static T* getInstancePtr()	{
                return instance;
            }
    };

    template <typename T> T* Singleton<T>::instance = 0;
}

#endif // SINGLETON_H_
