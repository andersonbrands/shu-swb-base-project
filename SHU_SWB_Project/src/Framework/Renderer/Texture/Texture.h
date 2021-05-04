/***************************************************************************************
*	Title: Texture.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <string>

using namespace std;

namespace Framework {

    class Texture {
        private:
        public:
            Texture() {}
            virtual ~Texture() {}

            virtual void load(const string &path, const string &filename) = 0;
    };

}

#endif // TEXTURE_H_
