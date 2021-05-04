/***************************************************************************************
*	Title: TraceHUD.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#include "TraceHUD.h"

#include "../Framework/Utilities/Timer.h"
#include "../WindowsPlatform\WindowsPlatformTask.h"
#include "../Framework\EventManager\EventId.h"
#include "../Framework\EventManager\EventManager.h"
#include "../WindowsPlatform/Input/DInputManager.h"

#include <sstream>

TraceHUD::TraceHUD() : font_(), count_(0), fps_(0.0f), show_(false) {
    font_.createFont("Lucida Console", 16, true);

    attachEvent(RENDER_EVENT, *this);
    attachEvent(UPDATE, *this);
}
TraceHUD::~TraceHUD() {
}

void TraceHUD::handleEvent(Event *pEvent) {
    switch (pEvent->getID()) {
        case RENDER_EVENT: {
            if (!show_)
                break;

            assert(Timer::getPtr());
            assert(WindowsPlatformTask::getInstancePtr());

            // get FPS every quarter of second, so that it doesn't twinkle too much
            int skip = Timer::getPtr()->UPDATES_PER_SECOND / 4;
            if (++count_ % skip == 0) {
                count_ = 0;
                fps_ = Timer::getPtr()->getFPS();
            }

            std::stringstream ss;

            ss << "FPS: " << fps_;
            int w(WindowsPlatformTask::getInstancePtr()->getBufferWidth());
            int h(WindowsPlatformTask::getInstancePtr()->getBufferHeight());
            ss << "\nWidth: " << w;
            ss << "\nHeight: " << h;

            ss << "\nGame time: " << Timer::getPtr()->getGameTime();
            font_.drawText(ss.str().c_str(), 10, 10, D3DCOLOR_XRGB(255, 255, 255), nullptr, w, h);
            break;
        }
        case UPDATE: {
            auto input(DInputManager::getInstancePtr());
            assert(input);
            if (input->onKeyDown(DIK_I)) {
                show_ = !show_;
            }
        }
        break;
        default:
            break;
    }
}