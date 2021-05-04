/***************************************************************************************
*	Title: TextureD3D.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef TEXTURE_D3D_H_
#define TEXTURE_D3D_H_

#include "../../../Framework/Renderer/Texture/Texture.h"
#include <d3dx9.h>
#include <cassert>

using namespace Framework;

class TextureD3D :public Texture {
    private:
    public:
        LPDIRECT3DTEXTURE9 texture_;
        TextureD3D();
        virtual ~TextureD3D();

        virtual void load(const string &path, const string &filename);

        LPDIRECT3DTEXTURE9* getTexture() {
            return &texture_;
        }
};

#endif // TEXTURE_D3D_H_
