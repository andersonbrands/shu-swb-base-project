/***************************************************************************************
*	Title: Timer.h
*	Author: Brandao, Anderson
*	Date: 2014
*
*	Based on original by Bruce Sutherland available at http://www.apress.com/9781430258308 (2014)
*
***************************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

#include "../Kernel/Task.h"
#include "../EventManager/EventHandler.h"

namespace Framework {
    class Timer : public Task, public EventHandler {
        public:
            typedef long long	TimeUnits;

            Timer(const unsigned int priority);
            virtual ~Timer();

            float			getTimeFrame() const;
            float			getTimeSim() const;
            void			setSimMultiplier(const float simMultiplier);
            float			getSimMultiplier();
            float			getFPS() const;
            float			getGameTime() const;

            virtual bool	start();
            virtual void 	onSuspend();
            virtual void 	update();
            virtual void 	onResume();
            virtual void 	stop();

            const int UPDATES_PER_SECOND;

            virtual void handleEvent(Event* pEvent);

            static Timer* getPtr()	{
                return instance_;
            }

        protected:
            virtual TimeUnits miliSecondsTime() const = 0;
            virtual void sleep(long) const = 0;

        private:
            long long getUpdateFrame() const;
            TimeUnits	timeLastFrame_;
            int			frameDt_;// delta frame in miliseconds
            float		simulationMultiplier_;
            TimeUnits	gameTime_;// game time in miliseconds

            // used to have a fixed frame rate
            long long currentUpdate_;
            long long nextUpdate_;


            static Timer* instance_;
    };

    inline float Timer::getFPS() const {
        return 1000.0f / (float)frameDt_;
    }

    // get total game time in seconds
    inline float Timer::getGameTime() const {
        const float MILI_TO_SECONDS_MULTIPLIER = 0.001f;
        return gameTime_ * MILI_TO_SECONDS_MULTIPLIER;
    }

    // get delta frame in seconds
    inline float Timer::getTimeFrame() const {
        const float MILI_TO_SECONDS_MULTIPLIER = 0.001f;
        return frameDt_ * MILI_TO_SECONDS_MULTIPLIER;
    }

    // get delta simulation time in seconds
    inline float Timer::getTimeSim() const {
        return getTimeFrame() * simulationMultiplier_;
    }

    inline void Timer::setSimMultiplier(const float simMultiplier) {
        simulationMultiplier_ = simMultiplier;
    }

    inline float Timer::getSimMultiplier() {
        return simulationMultiplier_;
    }
}

#endif // TIMER_H_
