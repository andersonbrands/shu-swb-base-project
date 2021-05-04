/***************************************************************************************
*	Title: GameTask.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef GAME_TASK_H_
#define GAME_TASK_H_

#include "../Framework\Kernel\Task.h"
#include "TraceHUD.h"
#include "../Framework\GameObjects\GameObject.h"
#include "GameObjects\Dice.h"
#include "GameObjects\Floor.h"
#include "GameObjects/PointLight.h"
#include "GameObjects\Camera.h"
#include "GameObjects\SpriteExplosion.h"

using namespace Framework;

class GameTask : public Task {
    private:
        TraceHUD* pTraceHUD_;

        Dice dice_;
        Floor floor1_;
        PointLight light_;
        Camera camera_;
        SpriteExplosion spriteAnimation_;

    public:
        GameTask(const unsigned int priority);
        virtual ~GameTask();

        virtual bool	start();
        virtual void 	onSuspend();
        virtual void 	update();
        virtual void 	onResume();
        virtual void 	stop();
};

#endif // GAME_TASK_H_
