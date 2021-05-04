/***************************************************************************************
*	Title: FontD3D.h
*	Author: Brandao, Anderson
*	Date: 2014
*
*	Based on original by Mark Featherstone (C) 2013 All Rights Reserved.
*
***************************************************************************************/


#ifndef FONT_D3D_H_
#define FONT_D3D_H_
#include <d3d9.h>
#include <d3dx9core.h>
#include "../../../Framework/EventManager/EventHandler.h"

using namespace Framework;

// Font alignment
namespace FontAlignment {
    typedef enum {
        FA_LEFT,
        FA_CENTRE,
        FA_RIGHT,
        FA_TOPRIGHT,
        FA_TOPLEFT,
        FA_BOTTOMRIGHT,
        FA_BOTTOMLEFT
    } Enum;
}

class FontD3D : public EventHandler {
    public:
        FontD3D();
        ~FontD3D();
        bool createFont( const char* faceName, int size, bool bold = FALSE, bool italic = FALSE );
        RECT drawText( const char* text, int xPosition, int yPosition, DWORD color, LPD3DXSPRITE sprite = NULL,
                       int textBoxWidth = 0, int textBoxHeight = 0, FontAlignment::Enum alignment = FontAlignment::FA_LEFT, bool dimensionsOnly=false ) const;

        virtual void handleEvent(Event* pEvent);
    private:
        LPD3DXFONT pFont_;
};

#endif // FONT_D3D_H_