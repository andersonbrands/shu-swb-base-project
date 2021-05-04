/***************************************************************************************
*	Title: SpriteD3D.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#include "SpriteD3D.h"
#include "../../WindowsPlatformTask.h"
#include "../Texture/TextureD3D.h"
#include "../../../Framework/Renderer/Texture/TextureManager.h"
#include "../../../Framework/Utilities/Utils.h"

const DWORD SpriteD3D::FVF_SPRITE_VERTEX = (D3DFVF_XYZ /*| D3DFVF_NORMAL*/ | D3DFVF_TEX1);

SpriteD3D::SpriteD3D() : vertices_(new SPRITE_VERTEX[4]), pVertexBuffer_(nullptr) {

}

SpriteD3D::~SpriteD3D() {
    if (vertices_) {
        delete[] vertices_;
        vertices_ = nullptr;
    }
    if (pVertexBuffer_) {
        pVertexBuffer_->Release();
        pVertexBuffer_ = nullptr;
    }
}

void SpriteD3D::setUVCoords(int index, float u, float v) {
    vertices_[index].u = u;
    vertices_[index].v = v;
}

void SpriteD3D::render() {
    assert(WindowsPlatformTask::getInstancePtr());

    TextureD3D *pTexture = static_cast<TextureD3D*>( pTexture_ );

    WindowsPlatformTask::getInstancePtr()->getDevice()->SetTexture(0, pTexture->texture_);

    WindowsPlatformTask::getInstancePtr()->getDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    WindowsPlatformTask::getInstancePtr()->getDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
    WindowsPlatformTask::getInstancePtr()->getDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    WindowsPlatformTask::getInstancePtr()->getDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

    WindowsPlatformTask::getInstancePtr()->getDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

    WindowsPlatformTask::getInstancePtr()->getDevice()->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);
    WindowsPlatformTask::getInstancePtr()->getDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

    WindowsPlatformTask::getInstancePtr()->getDevice()->SetStreamSource(0, pVertexBuffer_, 0, sizeof(SPRITE_VERTEX));
    WindowsPlatformTask::getInstancePtr()->getDevice()->SetFVF(FVF_SPRITE_VERTEX);
    WindowsPlatformTask::getInstancePtr()->getDevice()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

    WindowsPlatformTask::getInstancePtr()->getDevice()->SetTexture(0, nullptr);
}

const Vector3 SpriteD3D::getMin() const {
    float x, y, z;

    x = _min(vertices_[0].position.x, vertices_[1].position.x);
    x = _min(vertices_[2].position.x, x);
    x = _min(vertices_[3].position.x, x);

    y = _min(vertices_[0].position.y, vertices_[1].position.y);
    y = _min(vertices_[2].position.y, y);
    y = _min(vertices_[3].position.y, y);

    z = _min(vertices_[0].position.z, vertices_[1].position.z);
    z = _min(vertices_[2].position.z, z);
    z = _min(vertices_[3].position.z, z);

    return Vector3(x, y, z);
}
const Vector3 SpriteD3D::getMax() const {
    float x, y, z;

    x = _max(vertices_[0].position.x, vertices_[1].position.x);
    x = _max(vertices_[2].position.x, x);
    x = _max(vertices_[3].position.x, x);

    y = _max(vertices_[0].position.y, vertices_[1].position.y);
    y = _max(vertices_[2].position.y, y);
    y = _max(vertices_[3].position.y, y);

    z = _max(vertices_[0].position.z, vertices_[1].position.z);
    z = _max(vertices_[2].position.z, z);
    z = _max(vertices_[3].position.z, z);

    return Vector3(x, y, z);
}

void SpriteD3D::applySettings() {
    // top left
    vertices_[0].position = D3DXVECTOR3(0.0f,height_,0.0f);
    // top right
    vertices_[1].position = D3DXVECTOR3(width_,height_,0.0f);
    // bottom right
    vertices_[2].position = D3DXVECTOR3(width_,0.0f,0.0f);
    // bottom left
    vertices_[3].position = D3DXVECTOR3(0.0f,0.0f,0.0f);

    D3DXVECTOR3 normal(0,0,-1);

    // TODO: use normal
    /*
    vertices_[0].normal = normal;
    vertices_[1].normal = normal;
    vertices_[2].normal = normal;
    vertices_[3].normal = normal;
    */

    D3DXVECTOR3 offset(0, 0, 0);

    switch (align_) {
        case Framework::Sprite::BOTTOM_LEFT:
            // no offset needed
            createVertexBuffer();
            return;
        case Framework::Sprite::TOP_LEFT:
            offset = vertices_[0].position;
            break;
        case Framework::Sprite::TOP_RIGHT:
            offset = vertices_[1].position;
            break;
        case Framework::Sprite::BOTTOM_RIGHT:
            offset = vertices_[2].position;
            break;
        case Framework::Sprite::CENTER:
            offset = D3DXVECTOR3(width_/2.0f, height_/2.0f, 0);
            break;
        case Framework::Sprite::CENTER_LEFT:
            offset = D3DXVECTOR3(0, height_/2.0f, 0);
            break;
        case Framework::Sprite::CENTER_TOP:
            offset = D3DXVECTOR3(width_/2.0f, height_, 0);
            break;
        case Framework::Sprite::CENTER_RIGHT:
            offset = D3DXVECTOR3(width_, height_/2.0f, 0);
            break;
        case Framework::Sprite::CENTER_BOTTOM:
            offset = D3DXVECTOR3(width_/2.0f, 0, 0);
            break;
        default:
            return;
    }

    vertices_[0].position -= offset;
    vertices_[1].position -= offset;
    vertices_[2].position -= offset;
    vertices_[3].position -= offset;

    createVertexBuffer();
}

void SpriteD3D::createVertexBuffer() {

    const int numVertices(6);
    const int bufferSize(numVertices * sizeof(SPRITE_VERTEX));

    assert(WindowsPlatformTask::getInstancePtr());

    assert(!FAILED(WindowsPlatformTask::getInstancePtr()->getDevice()->CreateVertexBuffer(bufferSize, 0, FVF_SPRITE_VERTEX, D3DPOOL_DEFAULT, &pVertexBuffer_, nullptr)));

    SPRITE_VERTEX *pVertices( nullptr);

    assert(!FAILED(pVertexBuffer_->Lock(0, 0, (void**)&pVertices, 0)));

    pVertices[0] = vertices_[3];
    pVertices[1] = vertices_[0];
    pVertices[2] = vertices_[1];

    pVertices[3] = vertices_[3];
    pVertices[4] = vertices_[1];
    pVertices[5] = vertices_[2];

    pVertexBuffer_->Unlock();
}

