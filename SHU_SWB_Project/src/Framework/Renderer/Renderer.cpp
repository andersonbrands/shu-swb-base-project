/***************************************************************************************
*	Title: Renderer.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#include "Renderer.h"

namespace Framework {

    Renderer* Renderer::instance_ = nullptr;

    Renderer::Renderer(const unsigned int priority) : Task(priority) {
        instance_ = this;
    }

    Renderer::~Renderer() {

    }

}