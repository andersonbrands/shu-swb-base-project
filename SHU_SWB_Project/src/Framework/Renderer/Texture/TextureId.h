/***************************************************************************************
*	Title: TextureId.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef TEXTURE_ID_H_
#define TEXTURE_ID_H_

#include <string>

namespace Framework {

    typedef unsigned int TextureId;

    typedef struct {
        TextureId id;
        std::string name;
    } TextureIdAndName;

    //static const TextureIdAndName TEXTURE_NAME	= { id, name };
    static const TextureIdAndName TEXTURE_01		= { 0, "texture_01.jpg" };
    static const TextureIdAndName EXPLOSION_SPRITE	= { 1, "explosion.png" };
    static const TextureIdAndName MEMORY_SPRITE	= { 2, "memory_sheet.png" };
}

#endif // TEXTURE_ID_H_
