/***************************************************************************************
*	Title: TimerWindows.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#include "TimerWindows.h"

#include <Windows.h>

TimerWindows::TimerWindows(const unsigned int priority)
    : Timer(priority) {
    
}

TimerWindows::~TimerWindows() {
}

Timer::TimeUnits TimerWindows::miliSecondsTime() const {
    TimeUnits now(clock());
    // if (CLOCKS_PER_SEC != 1000)
    // now = ((float)clock() / CLOCKS_PER_SEC) * 1000.0f;
    return now;
}


void TimerWindows::sleep(long miliSeconds) const {
    Sleep(miliSeconds);
}