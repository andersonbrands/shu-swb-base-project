/***************************************************************************************
*	Title: SpriteD3D.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef SPRITE_D3D_H_
#define SPRITE_D3D_H_

#include "../../../Framework/Renderer/Sprite/Sprite.h"
#include "../../../Framework/Math/Vector3.h"
#include <d3dx9.h>

using namespace Framework;

class SpriteD3D : public Sprite {
    private:
        struct SPRITE_VERTEX {
            D3DXVECTOR3 position;
            //D3DXVECTOR3 normal;
            FLOAT u, v;
        };
        static const DWORD FVF_SPRITE_VERTEX;

        SPRITE_VERTEX *vertices_;

        LPDIRECT3DVERTEXBUFFER9 pVertexBuffer_;

        void createVertexBuffer();

    protected:
        virtual void applySettings();

    public:
        SpriteD3D();
        virtual ~SpriteD3D();

        void setUVCoords(int index, float u, float v);

        virtual void render();

        virtual const Vector3 getMin() const;
        virtual const Vector3 getMax() const;
};

#endif // SPRITE_D3D_H_
