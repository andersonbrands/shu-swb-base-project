/***************************************************************************************
*	Title: SoundId.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef SOUND_ID_H_
#define SOUND_ID_H_

#include <string>

namespace Framework {

    typedef unsigned int SoundId;

    typedef struct {
        SoundId id;
        std::string name;
    } SoundIdAndName;

    //static const SoundIdAndName SOUND_NAME = { id, "name" };
    static const SoundIdAndName LASER = { 0, "laser.wav" };

}

#endif // SOUND_ID_H_
