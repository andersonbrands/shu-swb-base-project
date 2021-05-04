/***************************************************************************************
*	Title: AudioManager.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#include "AudioManager.h"

namespace Framework {

    AudioManager* AudioManager::instance_ = nullptr;

    AudioManager::AudioManager(const std::string &audioDir) : AUDIO_DIR(audioDir) {
        instance_ = this;
    }

    AudioManager::~AudioManager() {

    }

}