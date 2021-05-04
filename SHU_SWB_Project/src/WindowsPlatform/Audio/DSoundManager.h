/***************************************************************************************
*	Title: DSoundManager.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef D_SOUND_MANAGER_H_
#define D_SOUND_MANAGER_H_

#include "../../Framework/Audio/AudioManager.h"
#include "../../Framework/Utilities/Singleton.h"

#include <dsound.h>

using namespace Framework;
using namespace std;

class DSoundManager : public AudioManager, public Singleton<DSoundManager> {
    private:
        IDirectSound8* device_;
        IDirectSoundBuffer* primaryBuffer_;

    public:
        DSoundManager(const string &audioDir);
        virtual ~DSoundManager();

        virtual void play(const SoundId& id, const float volume, bool loop) const;
        virtual void setVolume(const SoundId& id, const float volume) const;
        virtual void pause(const SoundId& id) const;
        virtual void stop(const SoundId& id) const;

        IDirectSound8* getDevice() {
            return device_;
        }
};

#endif // D_SOUND_MANAGER_H_
