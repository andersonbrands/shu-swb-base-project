/***************************************************************************************
*	Title: Color.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef COLOR_H_
#define COLOR_H_

namespace Framework {

    typedef struct ColorRGB {
        float r;
        float g;
        float b;
        ColorRGB(float _r, float _g, float _b) {
            r = _r;
            g = _g;
            b = _b;
        }
    } ColorRGB;

    typedef struct ColorARGB {
        float a;
        float r;
        float g;
        float b;
        ColorARGB(float _a, float _r, float _g, float _b) {
            a = _a;
            r = _r;
            g = _g;
            b = _b;
        }
    } ColorARGB;

}

#endif // COLOR_H_
