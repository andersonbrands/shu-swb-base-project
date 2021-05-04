/***************************************************************************************
*	Title: MemoryGameTask.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef MEMORY_GAME_TASK_H_
#define MEMORY_GAME_TASK_H_

#include "../Framework\Kernel\Task.h"
#include "TraceHUD.h"
#include "GameObjects\Camera.h"
#include "GameObjects\MemoryGame\Card.h"
#include "../Framework/Renderer/Texture/TextureManager.h"
#include "../Framework/Renderer/Sprite/SpriteManager.h"
#include "../Framework/EventManager/EventHandler.h"
#include "TextScreens.h"
#include <vector>

using namespace Framework;

class MemoryGameTask : public Task, public EventHandler {
        enum GameState {
            WELCOME_SCREEN,
            IN_GAME_SCREEN,
            GAME_OVER_SCREEN
        };
    private:
        TraceHUD* pTraceHUD_;
        TextScreens textScreens_;
        Camera camera_;

        std::vector<Card*> cards_;

        Card* first_;
        Card* second_;

        GameState state_;

        bool matchPending_;
        float matchPendingDeltaTime_;

    public:
        MemoryGameTask(const unsigned int priority);
        virtual ~MemoryGameTask();

        void setupCard(TextureManager* textureManager, SpriteManager* spriteManager, Card* card, int cardId);
        void placeCards();

        virtual bool	start();
        virtual void 	onSuspend();
        virtual void 	update();
        virtual void 	onResume();
        virtual void 	stop();

        virtual void handleEvent(Event* pEvent);

        void checkForMatch();
};

#endif // MEMORY_GAME_TASK_H_
