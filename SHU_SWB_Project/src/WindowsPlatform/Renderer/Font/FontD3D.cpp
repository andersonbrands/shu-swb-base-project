/***************************************************************************************
*	Title: FontD3D.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
*	Based on original by Mark Featherstone (C) 2013 All Rights Reserved.
*
***************************************************************************************/

#include "FontD3D.h"
#include "../../../Framework/EventManager/EventManager.h"
#include "../../WindowsPlatformTask.h"

FontD3D::FontD3D() : pFont_(nullptr) {
}
FontD3D::~FontD3D() {
    if( pFont_ )
        pFont_->Release();
    pFont_ = nullptr;
}

bool FontD3D::createFont( const char* faceName, int size, bool bold, bool italic ) {
    HRESULT hr = 0;
    assert(WindowsPlatformTask::getInstancePtr());
    hr = D3DXCreateFont( WindowsPlatformTask::getInstancePtr()->getDevice(), -size, 0, bold ? 800 : 0, 1, italic, DEFAULT_CHARSET,
                         OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, faceName, &pFont_ );
    if ( FAILED( hr ) ) {
        MessageBox(NULL, "D3DXCreateFont() failed.", "Error", MB_OK);
        return false;
    }

    attachEvent(ON_LOST_DEVICE, *this);
    attachEvent(ON_RESET_DEVICE, *this);

    return true;
}

RECT FontD3D::drawText( const char* text, int xPosition, int yPosition, DWORD color, LPD3DXSPRITE sprite,
                        int textBoxWidth, int textBoxHeight, FontAlignment::Enum alignment, bool dimensionsOnly ) const {
    RECT rect = {0,0,0,0};
    if ( !pFont_ ) {
        return rect;
    }
    DWORD format = DT_EXPANDTABS;
    if ( textBoxWidth == 0 ) {
        format |= DT_NOCLIP;
    } else {
        format |= DT_WORDBREAK;
        switch ( alignment ) {
            case FontAlignment::FA_LEFT:
                format |= DT_LEFT;
                break;
            case FontAlignment::FA_CENTRE:
                format |= DT_CENTER;
                break;
            case FontAlignment::FA_RIGHT:
                format |= DT_RIGHT;
                break;
            case FontAlignment::FA_TOPRIGHT:
                format |= DT_RIGHT | DT_TOP;
                break;
            case FontAlignment::FA_BOTTOMRIGHT:
                format |= DT_RIGHT | DT_BOTTOM;
                break;
            case FontAlignment::FA_TOPLEFT:
                format |= DT_LEFT | DT_TOP;
                break;
            case FontAlignment::FA_BOTTOMLEFT:
                format |= DT_LEFT | DT_BOTTOM;
                break;
        }
        if ( textBoxHeight == 0 ) {
            // A width is specified, but not a height.
            // Make it seem like height is infinite
            textBoxHeight = 2000;
        }
    }
    if(dimensionsOnly)
        format |= DT_CALCRECT;

    rect.left = xPosition;
    rect.top = yPosition;
    rect.right = xPosition + textBoxWidth;
    rect.bottom = yPosition + textBoxHeight;
    pFont_->DrawText( sprite, text, -1, &rect, format, color );

    return rect;
}

void FontD3D::handleEvent(Event* pEvent) {
    switch (pEvent->getID()) {
        case ON_LOST_DEVICE:
            if ( pFont_ )
                pFont_->OnLostDevice();

            break;
        case ON_RESET_DEVICE:
            if ( pFont_ )
                pFont_->OnResetDevice();

            break;
        default:
            break;
    }
}