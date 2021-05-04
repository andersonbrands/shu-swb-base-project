/***************************************************************************************
*	Title: Platform.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#include "Platform.h"

namespace Framework {
    bool Platform::isClosing_	= false;

    Platform::Platform(const unsigned int priority)
        :	Task(priority) {

    }

    Platform::~Platform() {
    }

}
