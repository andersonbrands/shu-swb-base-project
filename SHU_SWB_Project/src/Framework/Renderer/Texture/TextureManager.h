/***************************************************************************************
*	Title: TextureManager.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef TEXTURE_MANAGER_H_
#define TEXTURE_MANAGER_H_

#include "../../Utilities/UnorderedMapContainer.h"
#include "../../Utilities/Singleton.h"
#include "Texture.h"
#include "TextureId.h"
#include <string>

using namespace std;

namespace Framework {

    class TextureManager : public UnorderedMapContainer<TextureId, Texture>, public Singleton<TextureManager> {
        private:
            const string TEXTURE_DIR;
        public:
            TextureManager(const string &textureDir);
            virtual ~TextureManager();

            const string getDir() {
                return TEXTURE_DIR;
            }

            template <class T>
            T* loadTexture(const TextureIdAndName &idAndName);
            Texture* getTexture(const TextureId &id) {
                return getObject(id);
            }
    };

    template <class T>
    T* TextureManager::loadTexture(const TextureIdAndName &idAndName) {
        T* result = add<T>(idAndName.id);
        if (result)
            result->load(TEXTURE_DIR, idAndName.name);
        return result;
    }


}

#endif // TEXTURE_MANAGER_H_
