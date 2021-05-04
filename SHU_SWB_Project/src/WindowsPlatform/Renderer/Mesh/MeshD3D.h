/***************************************************************************************
*	Title: MeshD3D.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef MESH_D3D_H_
#define MESH_D3D_H_

#include "../../../Framework/Renderer/Mesh/Mesh.h"
#include <d3dx9.h>

#include <string>

using namespace std;
using namespace Framework;

class MeshD3D : public Mesh {
    public:
        MeshD3D();
        virtual ~MeshD3D();

        virtual void render();

        virtual void load(const string &path, const string &filename);
    protected:

    private:
        LPD3DXMESH			mesh_;						 // The mesh object
        D3DMATERIAL9		*meshMaterials_;			 // Materials for the mesh
        LPDIRECT3DTEXTURE9  *meshTextures_;				 // Textures for the mesh
        DWORD				numMaterials_;			 // Number of materials in the mesh
};

#endif // MESH_D3D_H_
