/***************************************************************************************
*	Title: Timer.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
*	Based on original by Bruce Sutherland available at http://www.apress.com/9781430258308 (2014)
*
***************************************************************************************/

#include "Timer.h"

#include "../EventManager/EventManager.h"


namespace Framework {

    Timer* Timer::instance_ = nullptr;

    Timer::Timer(const unsigned int priority)
        : Task(priority)
        , UPDATES_PER_SECOND(30)
        , timeLastFrame_(0)
        , frameDt_(0.0f)
        , simulationMultiplier_(1.0f)
        , gameTime_(0) {
        instance_ = this;
    }

    Timer::~Timer() {
    }

    bool Timer::start() {
        timeLastFrame_ = miliSecondsTime();

        currentUpdate_ = getUpdateFrame();
        nextUpdate_ = currentUpdate_;

        attachEvent(PLATFORM_SUSPEND, *this);
        attachEvent(PLATFORM_RESUME, *this);

        return true;
    }

    void Timer::onSuspend() {
        setSuspended(true);
    }

    void Timer::update() {
        if (isSuspended()) return;

        // fixed frame rate
        while (true) {
            nextUpdate_ = getUpdateFrame();
            if( nextUpdate_ != currentUpdate_ ) {
                break;
            }
            sleep(1);
        }
        currentUpdate_ = nextUpdate_;

        // keep track of delta times
        TimeUnits currentTime = miliSecondsTime();
        frameDt_ = currentTime-timeLastFrame_;
        timeLastFrame_ = currentTime;
        gameTime_ += frameDt_;
    }

    void Timer::onResume() {
        timeLastFrame_ = miliSecondsTime();

        currentUpdate_ = getUpdateFrame();
        nextUpdate_ = currentUpdate_;

        setSuspended(false);
    }

    void Timer::stop() {
    }

    //count up at desired frame rate
    long long Timer::getUpdateFrame() const {
        return (long long)(miliSecondsTime() / (1000/UPDATES_PER_SECOND));
    }

    void Timer::handleEvent(Event* pEvent) {
        switch (pEvent->getID()) {
            case PLATFORM_SUSPEND:
                onSuspend();
                break;
            case PLATFORM_RESUME:
                onResume();
            default:
                break;
        }
    }
}
