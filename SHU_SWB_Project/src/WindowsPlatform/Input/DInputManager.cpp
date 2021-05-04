/***************************************************************************************
*	Title: DInputManager.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
*	Based on original by Mark Featherstone (C) 2013 All Rights Reserved.
*
***************************************************************************************/

#include "DInputManager.h"

#include "../WindowsPlatformTask.h"
#include "../../Framework/EventManager/EventManager.h"
#include "../../Framework/EventManager/EventData.h"

DInputManager::DInputManager(const unsigned int priority) : Task(priority), mouseSensibility_(0.005f), mouseLeftButtonIsDown_(false), lastMouseLeftButtonIsDown_(false) {
    assert(WindowsPlatformTask::getInstancePtr());

    // Create the DirectInput object.
    if(FAILED(DirectInput8Create( WindowsPlatformTask::getInstancePtr()->getHInst(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mpDI_, nullptr)))
        MessageBox(NULL, "DInput8Create failed", "Error", MB_OK);

    // Retrieve a pointer to an IDirectInputDevice8 interface.
    if(FAILED(mpDI_->CreateDevice(GUID_SysKeyboard, &pDIKeyboardDevice_, nullptr)))
        MessageBox(NULL, "DInput CreateDevice failed", "Error", MB_OK);

    // Now that you have an IDirectInputDevice8 interface, get
    // ready to use it.

    // Set the data format using the predefined keyboard data format.
    if(FAILED(pDIKeyboardDevice_->SetDataFormat(&c_dfDIKeyboard)))
        MessageBox(NULL, "Failed to set data format for keyboard", "Error", MB_OK);

    // Set the cooperative level
    if(FAILED(pDIKeyboardDevice_->SetCooperativeLevel(WindowsPlatformTask::getInstancePtr()->getHWnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
        MessageBox(NULL, "Failed to set cooperative level of keyboard", "Error", MB_OK);

    pDIKeyboardDevice_->Acquire();

    ZeroMemory(&buffer_, BUFFER_SIZE);
    ZeroMemory(&lastBuffer_, BUFFER_SIZE);

    registerEvent(CAMERA_MOVE);


    if(FAILED(mpDI_->CreateDevice(GUID_SysMouse, &pDIMouseDevice_, nullptr)))
        MessageBox(NULL, "DInput CreateDevice failed", "Error", MB_OK);

    if(FAILED(pDIMouseDevice_->SetDataFormat(&c_dfDIMouse2)))
        MessageBox(NULL, "Failed to set data for mouse", "Error", MB_OK);

    if(FAILED(pDIMouseDevice_->SetCooperativeLevel(WindowsPlatformTask::getInstancePtr()->getHWnd(), DISCL_FOREGROUND|DISCL_EXCLUSIVE)))
        MessageBox(NULL, "Failed to set cooperative level for mouse", "Error", MB_OK);

    pDIMouseDevice_->Acquire();
}

DInputManager::~DInputManager() {
    if (mpDI_) {
        if (pDIKeyboardDevice_) {
            // Always unacquire device before calling Release().
            pDIKeyboardDevice_ -> Unacquire();
            pDIKeyboardDevice_ -> Release();
            pDIKeyboardDevice_ = nullptr;
        }
        if (pDIMouseDevice_) {
            // Always unacquire device before calling Release().
            pDIMouseDevice_->Unacquire();
            pDIMouseDevice_->Release();
            pDIMouseDevice_ = nullptr;
        }
        mpDI_ -> Release();
        mpDI_ = nullptr;
    }
}



void DInputManager::update() {
    if (isSuspended()) return;

    HRESULT hr;

    //remember what was down, so we know when something is pressed and released
    memcpy(lastBuffer_, buffer_, BUFFER_SIZE);

    // Clear the buffer for keyboard data - just in case.
    ZeroMemory(&buffer_, BUFFER_SIZE);

    hr = pDIKeyboardDevice_->GetDeviceState(sizeof(buffer_),(LPVOID)&buffer_);
    if FAILED(hr) {
        // If this failed, the device has probably been lost.
        // Check for (hr == DIERR_INPUTLOST) and attempt to reacquire it here.
        hr = pDIKeyboardDevice_->Acquire();
        while (hr == DIERR_INPUTLOST)
            hr = pDIKeyboardDevice_->Acquire();

        hr = pDIKeyboardDevice_->GetDeviceState(sizeof(buffer_),(LPVOID)&buffer_);
    }

    if (onKeyDown(DIK_F11)) {
        sendEvent(TOGGLE_FULLSCREEN);
    }
    
    MovementEventData m;

    if(onKeyDown(DIK_W)) {
        m.direction = Direction::FORWARD;
        sendEvent(CAMERA_MOVE, &m);
    } else if(onKeyUp(DIK_W)) {
        m.direction = Direction::BACKWARD;
        sendEvent(CAMERA_MOVE, &m);
    }
    if(onKeyDown(DIK_S)) {
        m.direction = Direction::BACKWARD;
        sendEvent(CAMERA_MOVE, &m);
    } else if(onKeyUp(DIK_S)) {
        m.direction = Direction::FORWARD;
        sendEvent(CAMERA_MOVE, &m);
    }
    if(onKeyDown(DIK_A)) {
        m.direction = Direction::LEFT;
        sendEvent(CAMERA_MOVE, &m);
    } else if(onKeyUp(DIK_A)) {
        m.direction = Direction::RIGHT;
        sendEvent(CAMERA_MOVE, &m);
    }
    if(onKeyDown(DIK_D)) {
        m.direction = Direction::RIGHT;
        sendEvent(CAMERA_MOVE, &m);
    } else if(onKeyUp(DIK_D)) {
        m.direction = Direction::LEFT;
        sendEvent(CAMERA_MOVE, &m);
    }
    if(onKeyDown(DIK_UPARROW)) {
        m.direction = Direction::UP;
        sendEvent(CAMERA_MOVE, &m);
    } else if(onKeyUp(DIK_UPARROW)) {
        m.direction = Direction::DOWN;
        sendEvent(CAMERA_MOVE, &m);
    }
    if(onKeyDown(DIK_DOWNARROW)) {
        m.direction = Direction::DOWN;
        sendEvent(CAMERA_MOVE, &m);
    } else if(onKeyUp(DIK_DOWNARROW)) {
        m.direction = Direction::UP;
        sendEvent(CAMERA_MOVE, &m);
    }
    

    DIMOUSESTATE2 MouseState;      // DirectInput mouse state structure

    // Get the input's device state and store it in 'MouseState'
    ZeroMemory(&MouseState, sizeof(MouseState));
    hr = pDIMouseDevice_ -> GetDeviceState(sizeof(DIMOUSESTATE2), &MouseState);
    if (FAILED(hr)) {
        hr = pDIMouseDevice_ -> Acquire();
        while (hr == DIERR_INPUTLOST) hr = pDIMouseDevice_ -> Acquire();

        hr = pDIMouseDevice_ -> GetDeviceState(sizeof(DIMOUSESTATE2), &MouseState);
    }

    mouseDeltaX_ = MouseState.lX * mouseSensibility_;
    mouseDeltaY_ = MouseState.lY * mouseSensibility_;

    lastMouseLeftButtonIsDown_ = mouseLeftButtonIsDown_;
    mouseLeftButtonIsDown_ = MouseState.rgbButtons[0] & 0x80;
}

bool DInputManager::start() {
    return true;
}

void DInputManager::onSuspend() {
    setSuspended(true);
}

void DInputManager::onResume() {
    setSuspended(false);
}
void DInputManager::stop() {

}