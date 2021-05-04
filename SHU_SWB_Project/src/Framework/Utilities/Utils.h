/***************************************************************************************
*	Title: Utils.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef UTILS_H_
#define UTILS_H_

namespace Framework {

    template<typename T>
    inline T _max(T a, T b) {
        return (a > b)? a : b;
    }

    template<typename T>
    inline T _min(T a, T b) {
        return (a < b)? a : b;
    }

    enum Direction {
        FORWARD, BACKWARD, UP, DOWN, RIGHT, LEFT
    };

}

#endif // !UTILS_H_
