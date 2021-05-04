#ifndef MESH_ID_H_
#define MESH_ID_H_

#include <string>

namespace Framework {

    typedef unsigned int MeshId;

    typedef struct {
        MeshId id;
        std::string name;
    } MeshIdAndName;

    //static const MeshIdAndName MESH_NAME	= { id, name };
    static const MeshIdAndName MESH_DICE = { 0, "dice.x"};
    static const MeshIdAndName MESH_FLOOR_1 = { 1, "floor_1.x"};
    static const MeshIdAndName MESH_SPHERE_FLIPPED_N = { 2, "sphere_flipped_n.x"};
    static const MeshIdAndName MESH_SPHERE = { 3, "sphere.x"};

}

#endif // MESH_ID_H_
