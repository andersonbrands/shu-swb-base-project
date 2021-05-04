/***************************************************************************************
*	Title: TraceHUD.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef TRACE_HUD_H_
#define TRACE_HUD_H_

#include "../Framework\EventManager\EventHandler.h"
#include "../WindowsPlatform\Renderer\Font\FontD3D.h"

class TraceHUD : public EventHandler {
    private:
        FontD3D font_;
        byte count_;
        float fps_;

        bool show_;
    public:
        TraceHUD();
        ~TraceHUD();

        virtual void handleEvent(Event *pEvent);
};


#endif // !TRACE_HUD_H_
