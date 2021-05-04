/***************************************************************************************
*	Title: Kernel.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
*	Based on original by Bruce Sutherland available at http://www.apress.com/9781430258308 (2014)
*
***************************************************************************************/

#include "Kernel.h"

#include "../Platform/Platform.h"

namespace Framework {
    Kernel::Kernel() {
    }

    Kernel::~Kernel() {
    }

    void Kernel::priorityAdd(Task* pTask) {
        TaskListIterator iter;
        for (iter = tasks_.begin(); iter != tasks_.end(); ++iter) {
            Task* pCurrentTask = (*iter);
            if (pCurrentTask->getPriority() > pTask->getPriority()) {
                break;
            }
        }
        tasks_.insert(iter, pTask);
    }

    void Kernel::execute() {
        while (tasks_.size()) {
            if (Platform::isClosing()) {
                killAllTasks();
            }

            TaskListIterator iter;
            for (iter = tasks_.begin(); iter != tasks_.end(); ++iter) {
                Task* pTask = (*iter);
				if (!pTask->canKill()) {
                    pTask->update();
                }
            }

            for (iter = tasks_.begin(); iter != tasks_.end();) {
                Task* pTask = (*iter);
                ++iter;
                if (pTask->canKill()) {
                    pTask->stop();
                    tasks_.remove(pTask);
                    pTask = 0;
                }
            }
        }

        Platform::clearClosing();
    }

    bool Kernel::addTask(Task* pTask) {
        bool started = pTask->start();

        if (started) {
            priorityAdd(pTask);
        }
        return started;
    }

    void Kernel::suspendTask(Task* pTask) {
        // Ensure that task is running
        if (std::find(tasks_.begin(), tasks_.end(), pTask) != tasks_.end()) {
            pTask->onSuspend();
            tasks_.remove(pTask);
            pausedTasks_.push_back(pTask);
        }
    }

    void Kernel::resumeTask(Task* pTask) {
        if (std::find(pausedTasks_.begin(), pausedTasks_.end(), pTask) != pausedTasks_.end()) {
            pTask->onResume();
            pausedTasks_.remove(pTask);

            priorityAdd(pTask);
        }
    }

    void Kernel::removeTask(Task* pTask) {
        if (std::find(tasks_.begin(), tasks_.end(), pTask) != tasks_.end()) {
            pTask->setCanKill(true);
        }
    }

    void Kernel::killAllTasks() {
        for (TaskListIterator iter = tasks_.begin(); iter != tasks_.end(); ++iter) {
            (*iter)->setCanKill(true);
        }
    }
}
