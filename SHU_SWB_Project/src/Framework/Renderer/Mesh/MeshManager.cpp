/***************************************************************************************
*	Title: MeshManager.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#include "MeshManager.h"

namespace Framework {

    MeshManager::MeshManager(const string &meshDir) : UnorderedMapContainer(), MESH_DIR(meshDir) {

    }
    MeshManager::~MeshManager() {

    }

    Mesh* MeshManager::getMesh(const MeshIdAndName &idAndName) {
        return getObject(idAndName.id);
    }

}