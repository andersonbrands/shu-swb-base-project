/***************************************************************************************
*	Title: Wave.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef WAVE_H_
#define WAVE_H_

#include <cassert>
#include "SoundObject.h"
#include "../Utilities/Utils.h"

using namespace std;

namespace Framework {

    class Wave : public SoundObject {
        private:
            typedef struct {
                char chunkId[4];
                unsigned long chunkSize;
                char format[4];
                char subChunkId[4];
                unsigned long subChunkSize;
                unsigned short audioFormat;
                unsigned short numChannels;
                unsigned long sampleRate;
                unsigned long bytesPerSecond;
                unsigned short blockAlign;
                unsigned short bitsPerSample;
                char dataChunkId[4];
                unsigned long dataChunkSize;
            } WaveHeader;

            WaveHeader header_;

            bool headerIsValid() const;

        public:
            Wave();
            virtual ~Wave();

            virtual bool load(const string& filename);

            virtual void aquireData(unsigned char* data) = 0;

            const WaveHeader getHeader() {
                return header_;
            }
    };

}

#endif // WAVE_H_
