/***************************************************************************************
*	Title: TextScreens.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#include "TextScreens.h"
#include "../Framework/EventManager/EventManager.h"
#include "../WindowsPlatform/WindowsPlatformTask.h"

TextScreens::TextScreens() : font_(), welcomeText_("Memory game\nPress space to play"), gameOverText_("Game Over\nPress space to play again"), current_(nullptr), show_(true) {
    font_.createFont("Lucida Console", 20, true);

    attachEvent(RENDER_EVENT, *this);
}

TextScreens::~TextScreens() {

}

void TextScreens::handleEvent(Event *pEvent) {
    switch (pEvent->getID()) {
        case RENDER_EVENT: {
            if (!show_) return;
            auto win(WindowsPlatformTask::getInstancePtr());
            assert(win);
            int w(win->getBufferWidth());
            int h(win->getBufferHeight());

            if (current_)
                font_.drawText(current_->c_str(), 0, 0, D3DCOLOR_XRGB(255, 255, 255), nullptr, w, h, FontAlignment::FA_CENTRE);
            break;
        }
        default:
            break;
    }
}
void TextScreens::onStart() {
    current_ = &welcomeText_;
    show_ = true;
}
void TextScreens::onPlay() {
    show_ = false;
}
void TextScreens::onGameOver() {
    current_ = &gameOverText_;
    show_ = true;
}

