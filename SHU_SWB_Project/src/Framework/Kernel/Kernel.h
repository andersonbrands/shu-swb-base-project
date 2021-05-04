/***************************************************************************************
*	Title: Kernel.h
*	Author: Brandao, Anderson
*	Date: 2014
*
*	Based on original by Bruce Sutherland available at http://www.apress.com/9781430258308 (2014)
*
***************************************************************************************/

#ifndef KERNEL_H_
#define KERNEL_H_

#include <list>
#include "Task.h"

namespace Framework {
    class Kernel {
        private:
            typedef std::list<Task*>			TaskList;
            typedef std::list<Task*>::iterator	TaskListIterator;

            TaskList	tasks_;
            TaskList	pausedTasks_;

            void		priorityAdd(Task* pTask);

        public:
            Kernel();
            virtual ~Kernel();

            void	execute();

            bool 	addTask(Task* pTask);
            void	suspendTask(Task* task);
            void	resumeTask(Task* task);
            void	removeTask(Task* task);
            void	killAllTasks();

            bool	hasTasks()	{
                return (tasks_.size() != 0);
            }
    };
}

#endif // KERNEL_H_
