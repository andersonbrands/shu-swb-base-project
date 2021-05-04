/***************************************************************************************
*	Title: TextScreens.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef TEXT_SCREENS_H_
#define TEXT_SCREENS_H_

#include "../Framework\EventManager\EventHandler.h"
#include "../WindowsPlatform\Renderer\Font\FontD3D.h"
#include <string>

class TextScreens : public EventHandler {
    private:
        FontD3D font_;
        const std::string welcomeText_;
        const std::string gameOverText_;
        const std::string* current_;
        bool show_;
    public:
        TextScreens();
        virtual ~TextScreens();

        virtual void handleEvent(Event *pEvent);

        void onStart();
        void onPlay();
        void onGameOver();
};

#endif // TEXT_SCREENS_H_
