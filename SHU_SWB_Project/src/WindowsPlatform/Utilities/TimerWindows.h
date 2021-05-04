/***************************************************************************************
*	Title: TimerWindows.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef TIMER_WINDOWS_H_
#define TIMER_WINDOWS_H_

#include "../../Framework/Utilities/Timer.h"
#include "../../Framework/Utilities/Singleton.h"
#include <time.h>

using namespace Framework;

class TimerWindows : public Timer, public Singleton<TimerWindows> {
    public:
        TimerWindows(const unsigned int priority);
        ~TimerWindows();

    protected:
        virtual TimeUnits miliSecondsTime() const ;
		virtual void sleep(long) const;
};

#endif // TIMER_WINDOWS_H_
