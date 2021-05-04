/***************************************************************************************
*	Title: Application.h
*	Author: Brandao, Anderson
*	Date: 2014
*	
*	Based on original by Bruce Sutherland available at http://www.apress.com/9781430258308 (2014)
*
***************************************************************************************/

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "../Kernel/Kernel.h"

namespace Framework {
    class Application {
        protected:
            Kernel kernel_;

            virtual void createSingletons() = 0;
            virtual void destroySingletons() = 0;

        public:
            explicit Application() { }
            virtual ~Application() { }

            virtual bool	initialize() = 0;
            virtual void	run() {
                kernel_.execute();
                destroySingletons();
            }
    };
}

#endif // APPLICATION_H_
