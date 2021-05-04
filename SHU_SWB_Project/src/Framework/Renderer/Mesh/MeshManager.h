/***************************************************************************************
*	Title: MeshManager.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef MESH_MANAGER_H_
#define MESH_MANAGER_H_

#include <unordered_map>
#include "../../Utilities/Singleton.h"
#include "../../Utilities/UnorderedMapContainer.h"
#include "MeshId.h"
#include "Mesh.h"
#include <string>
#include <cassert>

using namespace std;

namespace Framework {

    class MeshManager : public UnorderedMapContainer<MeshId, Mesh>, public Singleton<MeshManager> {
        private:
            const string MESH_DIR;

        public:
            MeshManager(const string &meshDir);
            ~MeshManager();

            const string getDir() {
                return MESH_DIR;
            }

            template <class T>
            T* loadMesh(const MeshIdAndName &idAndName);
            Mesh* getMesh(const MeshIdAndName &idAndName);
    };

    template <class T>
    T* MeshManager::loadMesh(const MeshIdAndName &idAndName) {
        T* result = add<T>(idAndName.id);
        if (result)
            result->load(MESH_DIR, idAndName.name);
        return result;
    }
}

#endif // MESH_MANAGER_H_
