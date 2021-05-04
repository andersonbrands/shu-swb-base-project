/***************************************************************************************
*	Title: DInputManager.h
*	Author: Brandao, Anderson
*	Date: 2014
*
*	Based on original by Mark Featherstone (C) 2013 All Rights Reserved.
*
***************************************************************************************/

#ifndef D_INPUT_MANAGER_H
#define D_INPUT_MANAGER_H

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif


#include <dinput.h>

#include "../../Framework/Utilities/Singleton.h"
#include "../../Framework/Kernel/Task.h"

class DInputManager : public Framework::Task, public Framework::Singleton<DInputManager> {
    public:
        DInputManager(const unsigned int priority);
        virtual ~DInputManager();

        virtual bool start();
        virtual void onSuspend();
        virtual void update();
        virtual void onResume();
        virtual void stop();

        bool isMouseLeftButtonDown() {
            return mouseLeftButtonIsDown_;
        }
        bool onMouseLeftButtonDown() {
            return mouseLeftButtonIsDown_ && !lastMouseLeftButtonIsDown_;
        }

        bool isKeyDown(unsigned char dikCode) {
            return (buffer_[dikCode] & 0x80) ? true : false;
        }
        bool onKeyDown(unsigned char dikCode) {
            return isKeyDown(dikCode) && !(lastBuffer_[dikCode]&0x80);
        }
        //have they pressed AND then let go?
        bool onKeyUp(unsigned char dikCode) {
            return !isKeyDown(dikCode) && (lastBuffer_[dikCode]&0x80);
        }

        float getDeltaX() {
            return mouseDeltaX_;
        }
        float getDeltaY() {
            return mouseDeltaY_;
        }

    private:
        static const int BUFFER_SIZE = 256;			//keyboards are fixed size
        LPDIRECTINPUT8 mpDI_;						//main device context
        LPDIRECTINPUTDEVICE8 pDIKeyboardDevice_;	//keyboard interface
        LPDIRECTINPUTDEVICE8 pDIMouseDevice_;	//mouse interface
        float mouseDeltaX_;
        float mouseDeltaY_;
        float mouseSensibility_;
        char buffer_[BUFFER_SIZE];
        char lastBuffer_[BUFFER_SIZE];				//remember what was down previously for press+release
        bool mouseLeftButtonIsDown_;
        bool lastMouseLeftButtonIsDown_;
};

#endif // D_INPUT_MANAGER_H