/***************************************************************************************
*	Title: AudioManager.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef AUDIO_MANAGER_H_
#define AUDIO_MANAGER_H_

#include "../Utilities/UnorderedMapContainer.h"
#include <string>
#include <unordered_map>
#include "SoundId.h"
#include "SoundObject.h"

namespace Framework {

    class AudioManager : public UnorderedMapContainer<SoundId, SoundObject> {
        private:
            static AudioManager* instance_;
            const std::string AUDIO_DIR;
        public:
            AudioManager(const std::string &audioDir);
            virtual ~AudioManager();

            template <class T>
            T* loadSound(const SoundIdAndName &idAndName) {
                return add<T>(idAndName.id);
            }

            const string getDir() {
                return AUDIO_DIR;
            }

            static AudioManager* getPtr() {
                return instance_;
            }

            virtual void play(const SoundId& id, const float volume, bool loop) const = 0;
            virtual void setVolume(const SoundId& id, const float volume) const = 0;
            virtual void pause(const SoundId& id) const = 0;
            virtual void stop(const SoundId& id) const = 0;
    };
    
}

#endif // AUDIO_MANAGER_H_
