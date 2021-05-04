#ifndef COMPONENT_ID_H_
#define COMPONENT_ID_H_

namespace Framework {
    typedef unsigned int ComponentId;

    //static const ComponentId COMPONENT_ID_COMPONENT_NAME	= value;
    static const ComponentId COMPONENT_ID_TRANSFORM	= 0;
    static const ComponentId COMPONENT_ID_MESH	= 1;
    static const ComponentId COMPONENT_ID_LIGHT	= 2;
    static const ComponentId COMPONENT_ID_CAMERA = 3;
    static const ComponentId COMPONENT_ID_AABB_COLLIDER = 4;
    static const ComponentId COMPONENT_ID_MOVEMENT = 5;
    static const ComponentId COMPONENT_ID_SPRITE_ANIMATION = 6;

}

#endif // COMPONENT_ID_H_
