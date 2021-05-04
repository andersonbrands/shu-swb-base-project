/***************************************************************************************
*	Title: SoundObject.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef SOUND_OBJECT_H_
#define SOUND_OBJECT_H_

#include <string>

namespace Framework {

    class SoundObject {
        private:
        public:
            SoundObject() {}
            virtual ~SoundObject() {}

            virtual bool load(const std::string& filename) = 0;
    };

}

#endif // SOUND_OBJECT_H_
