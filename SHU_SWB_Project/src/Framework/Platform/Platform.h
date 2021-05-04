/***************************************************************************************
*	Title: Platform.h
*	Author: Brandao, Anderson
*	Date: 2014
*
*	Based on original (Android.h) by Bruce Sutherland available at http://www.apress.com/9781430258308 (2014)
*
***************************************************************************************/

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "../Kernel/Task.h"

namespace Framework {

    class Platform : public Task {
        protected:
            static bool		isClosing_;

        public:
            Platform(const unsigned int priority);
            virtual ~Platform();

            virtual bool	start()		= 0;
            virtual void	onSuspend()	= 0;
            virtual void	update()	= 0;
            virtual void	onResume()	= 0;
            virtual void	stop()		= 0;

            static void clearClosing() {
                isClosing_ = false;
            }
            static bool isClosing()	{
                return isClosing_;
            }
    };
}

#endif // PLATFORM_H_
