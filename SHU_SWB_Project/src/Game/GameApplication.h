/***************************************************************************************
*	Title: GameApplication.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef GAME_APPLICATION_H_
#define GAME_APPLICATION_H_

#include "../Framework\Application\Application.h"


#include "MemoryGameTask.h"
typedef MemoryGameTask GameTask;

using namespace Framework;

class GameApplication : public Application {
private:
    GameTask* pGameTask_;
protected:
    virtual void createSingletons();
    virtual void destroySingletons();

public:
    explicit GameApplication();
    virtual ~GameApplication();

    virtual bool	initialize();
};

#endif // GAME_APPLICATION_H_
