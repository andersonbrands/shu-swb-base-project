/***************************************************************************************
*	Title: Task.h
*	Author: Brandao, Anderson
*	Date: 2014
*
*	Based on original by Bruce Sutherland available at http://www.apress.com/9781430258308 (2014)
*
***************************************************************************************/

#ifndef TASK_H_
#define TASK_H_

namespace Framework {
    class Task {
        private:
            unsigned int	priority_;
            bool			canKill_;
            bool			suspended_;

        public:
            explicit Task(const unsigned int priority);
            virtual ~Task();

            virtual bool	start()		= 0;
            virtual void	onSuspend()	= 0;
            virtual void	update()	= 0;
            virtual void	onResume()	= 0;
            virtual void	stop()		= 0;

            void 			setSuspended(const bool suspended);
            bool			isSuspended() const;
            void 			setCanKill(const bool canKill);
            bool			canKill() const;
            unsigned int	getPriority() const;

            static const unsigned int	TIMER_PRIORITY		= 0;
            static const unsigned int	PLATFORM_PRIORITY	= 1000;
            static const unsigned int	FILE_PRIORITY		= 2000;
            static const unsigned int	INPUT_PRIORITY		= 3000;
            static const unsigned int	GAME_PRIORITY		= 4000;
            static const unsigned int	AUDIO_PRIORITY		= 5000;
            static const unsigned int	RENDER_PRIORITY		= 6000;
    };

    inline Task::Task(const unsigned int priority) : priority_(priority), canKill_(false), suspended_(false) {

    }

    inline Task::~Task() {
    }

    inline void Task::setSuspended(const bool suspended) {
        suspended_ = suspended;
    }

    inline bool Task::isSuspended() const {
        return suspended_;
    }

    inline void Task::setCanKill(const bool canKill) {
        canKill_ = canKill;
    }

    inline bool Task::canKill() const {
        return canKill_;
    }

    inline unsigned int	Task::getPriority() const {
        return priority_;
    }
}

#endif // TASK_H_
