/***************************************************************************************
*	Title: WaveDBuffer.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef WAVE_D_BUFFER_H_
#define WAVE_D_BUFFER_H_

#include "../../Framework/Audio/Wave.h"
#include <dsound.h>

using namespace Framework;

class WaveDBuffer :public Wave {
    private:
        IDirectSoundBuffer8* secondaryBuffer_;
    public:
        WaveDBuffer();
        virtual ~WaveDBuffer();

        virtual void aquireData(unsigned char* data);

        IDirectSoundBuffer8* getBuffer() {
            return secondaryBuffer_;
        }
};

#endif // WAVE_D_BUFFER_H_
