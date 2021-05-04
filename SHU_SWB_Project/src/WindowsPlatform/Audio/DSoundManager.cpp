/***************************************************************************************
*	Title: DSoundManager.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#include "DSoundManager.h"
#include "../WindowsPlatformTask.h"
#include "WaveDBuffer.h"
#include "../../Framework/Utilities/Utils.h"

DSoundManager::DSoundManager(const string &audioDir) : AudioManager(audioDir) {
    HRESULT result;

    result = DirectSoundCreate8(nullptr, &device_, nullptr);

    assert(!FAILED(result));

    assert(WindowsPlatformTask::getInstancePtr());

    result = device_->SetCooperativeLevel(WindowsPlatformTask::getInstancePtr()->getHWnd(), DSSCL_PRIORITY);

    assert(!FAILED(result));

    WAVEFORMATEX wfx;

    wfx.wFormatTag = WAVE_FORMAT_PCM;
    wfx.nSamplesPerSec = 44100;
    wfx.wBitsPerSample = 16;
    wfx.nChannels = 2;
    wfx.nBlockAlign = (wfx.wBitsPerSample / 8) * wfx.nChannels;
    wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;
    wfx.cbSize = 0;

    DSBUFFERDESC bufferDesc;
    bufferDesc.dwSize = sizeof(DSBUFFERDESC);
    bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
    bufferDesc.dwBufferBytes = 0;
    bufferDesc.dwReserved = 0;
    bufferDesc.lpwfxFormat = nullptr;
    bufferDesc.guid3DAlgorithm = GUID_NULL;

    result = device_->CreateSoundBuffer(&bufferDesc, &primaryBuffer_, nullptr);
    assert(!FAILED(result));

    result = primaryBuffer_->SetFormat(&wfx);
    assert(!FAILED(result));
}

DSoundManager::~DSoundManager() {
    // release secondary buffers
    UnorderedMapContainer::clear();

    // release primary buffer
    if (primaryBuffer_) {
        primaryBuffer_->Release();
        primaryBuffer_ = nullptr;
    }

    // release sound device
    if (device_) {
        device_->Release();
        device_ = nullptr;
    }
}

void DSoundManager::setVolume(const SoundId& id, const float volume) const {
    float v(_max(_min(1.0f, volume), 0.0f));

    v = 1.0f - v;

    v *= DSBVOLUME_MIN;

    WaveDBuffer* pWBuffer (static_cast<WaveDBuffer*>( getInstancePtr()->getObject(id)) );

    if (pWBuffer) {

        pWBuffer->getBuffer()->SetVolume((LONG)v);

    }
}

void DSoundManager::play(const SoundId& id, const float volume, bool loop) const {
    WaveDBuffer* pWBuffer (static_cast<WaveDBuffer*>( getInstancePtr()->getObject(id)) );

    if (pWBuffer) {

        pWBuffer->getBuffer()->SetCurrentPosition(0);

        DWORD flags(0);
        if(loop)
            flags|=DSBPLAY_LOOPING;

        setVolume(id, volume);

        pWBuffer->getBuffer()->Play(0, 0, flags);

    }

}
void DSoundManager::pause(const SoundId& id) const {
    // TODO: pause sound
}
void DSoundManager::stop(const SoundId& id) const {
    WaveDBuffer* pWBuffer (static_cast<WaveDBuffer*>( getInstancePtr()->getObject(id)) );

    if (pWBuffer) {
        pWBuffer->getBuffer()->Stop();
    }
}
