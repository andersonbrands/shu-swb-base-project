/***************************************************************************************
*	Title: WaveDBuffer.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#include "WaveDBuffer.h"
#include "DSoundManager.h"

WaveDBuffer::WaveDBuffer() : secondaryBuffer_(nullptr) {

}

WaveDBuffer::~WaveDBuffer() {
    if (secondaryBuffer_) {
        secondaryBuffer_->Release();
        secondaryBuffer_ = nullptr;
    }
}

void WaveDBuffer::aquireData(unsigned char* data) {
    HRESULT result;

    WAVEFORMATEX wfx;

    wfx.wFormatTag = WAVE_FORMAT_PCM;
    wfx.nSamplesPerSec = getHeader().sampleRate;
    wfx.wBitsPerSample = 16;
    wfx.nChannels = getHeader().numChannels;
    wfx.nBlockAlign = (wfx.wBitsPerSample / 8) * wfx.nChannels;
    wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;
    wfx.cbSize = 0;

    DSBUFFERDESC bufferDesc;

    bufferDesc.dwSize = sizeof(DSBUFFERDESC);
    bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY;
    bufferDesc.dwBufferBytes = getHeader().dataChunkSize;
    bufferDesc.dwReserved = 0;
    bufferDesc.lpwfxFormat = &wfx;
    bufferDesc.guid3DAlgorithm = GUID_NULL;

    IDirectSoundBuffer* tempBuffer(nullptr);

    assert(DSoundManager::getInstancePtr());
    // Create a temporary sound buffer with the specific buffer settings.
    result = DSoundManager::getInstancePtr()->getDevice()->CreateSoundBuffer(&bufferDesc, &tempBuffer, nullptr);
    assert(!FAILED(result));

    // Test the buffer format against the direct sound 8 interface and create the secondary buffer.
    result = tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&secondaryBuffer_);

    assert(!FAILED(result));

    // Release the temporary buffer.
    tempBuffer->Release();
    tempBuffer = nullptr;

    unsigned char* bufferPtr;
    unsigned long bufferSize;

    // Lock the secondary buffer to write wave data into it.
    result = secondaryBuffer_->Lock(0, getHeader().dataChunkSize, (void**)&bufferPtr, (DWORD*)&bufferSize, nullptr, 0, 0);

    assert(!FAILED(result));

    // Copy the wave data into the buffer.
    memcpy(bufferPtr, data, getHeader().dataChunkSize);

    // Unlock the secondary buffer after the data has been written to it.
    result = secondaryBuffer_->Unlock((void*)bufferPtr, bufferSize, nullptr, 0);

    assert(!FAILED(result));
}

