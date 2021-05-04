/***************************************************************************************
*	Title: Wave.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#include "Wave.h"
#include <stdio.h>

namespace Framework {

    Wave::Wave() : SoundObject() {

    }

    Wave::~Wave() {

    }

    bool Wave::load(const string& filename) {
        FILE* pFile;

        assert(fopen_s(&pFile, filename.c_str(), "rb") == 0);

        assert(fread(&header_, sizeof(WaveHeader), 1, pFile) == 1);

        assert(headerIsValid());

        unsigned char* data = new unsigned char[header_.dataChunkSize];

        fseek(pFile, sizeof(WaveHeader), SEEK_SET);

        assert(fread(data, 1, header_.dataChunkSize, pFile) == header_.dataChunkSize);


        assert(fclose(pFile) == 0);

        aquireData(data);

        if (data)
            delete [] data;
        data = nullptr;

        return true;
    }

    bool Wave::headerIsValid() const {
        bool valid(true);

        if((header_.chunkId[0] != 'R') || (header_.chunkId[1] != 'I') ||
                (header_.chunkId[2] != 'F') || (header_.chunkId[3] != 'F')) {
            return false;
        }

        if((header_.format[0] != 'W') || (header_.format[1] != 'A') ||
                (header_.format[2] != 'V') || (header_.format[3] != 'E')) {
            return false;
        }

        if((header_.subChunkId[0] != 'f') || (header_.subChunkId[1] != 'm') ||
                (header_.subChunkId[2] != 't') || (header_.subChunkId[3] != ' ')) {
            return false;
        }

        if((header_.dataChunkId[0] != 'd') || (header_.dataChunkId[1] != 'a') ||
                (header_.dataChunkId[2] != 't') || (header_.dataChunkId[3] != 'a')) {
            return false;
        }

        return valid;
    }

}
