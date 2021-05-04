/***************************************************************************************
*	Title: TextureD3D.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#include "TextureD3D.h"
#include "../../WindowsPlatformTask.h"

TextureD3D::TextureD3D() : Texture() {

}

TextureD3D::~TextureD3D() {
    if (texture_) {
        texture_->Release();
        texture_ = nullptr;
    }
}

void TextureD3D::load(const string &path, const string &filename) {
    assert(WindowsPlatformTask::getInstancePtr());
    assert(!FAILED(D3DXCreateTextureFromFile(WindowsPlatformTask::getInstancePtr()->getDevice(), (path+filename).c_str(), &texture_)));
}

