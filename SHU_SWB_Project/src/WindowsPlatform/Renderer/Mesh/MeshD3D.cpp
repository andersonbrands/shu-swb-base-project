/***************************************************************************************
*	Title: MeshD3D.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#include "MeshD3D.h"

#include "../../WindowsPlatformTask.h"

MeshD3D::MeshD3D() : Mesh() {
}

MeshD3D::~MeshD3D() {
    if (meshMaterials_ != NULL) {
        delete[] meshMaterials_;
        meshMaterials_ = nullptr;
    }

    if (meshTextures_) {
        for (DWORD i(0); i < numMaterials_; ++i) {
            if(meshTextures_[i])
                meshTextures_[i] -> Release();
        }
        delete[] meshTextures_;
        meshTextures_=nullptr;
    }
    if (mesh_ != NULL) {
        mesh_ -> Release();
        mesh_ = nullptr;
    }
}

void MeshD3D::render() {
    assert(WindowsPlatformTask::getInstancePtr());

    for (DWORD i(0); i < numMaterials_; ++i) {
        // Select a material and texture.
        if(meshMaterials_)
            WindowsPlatformTask::getInstancePtr()->getDevice()->SetMaterial(&(meshMaterials_[i]));
        if(meshTextures_)
            WindowsPlatformTask::getInstancePtr()->getDevice()->SetTexture(0, meshTextures_[i]);
        // Render the section that uses this material and texture.
        mesh_->DrawSubset(i);
    }
}

void MeshD3D::load(const string &path, const string &filename) {
    LPD3DXBUFFER pD3DXMtrlBuffer;

    assert(WindowsPlatformTask::getInstancePtr());

    HRESULT hr;

    hr = D3DXLoadMeshFromX((path + filename).c_str(), D3DXMESH_MANAGED,
                           WindowsPlatformTask::getInstancePtr()->getDevice(),
                           NULL,
                           &pD3DXMtrlBuffer,
                           NULL,
                           &numMaterials_,
                           &mesh_);

    if FAILED(hr) {
        switch(hr) {
            case E_OUTOFMEMORY:
                MessageBox(NULL, "No Memory!", "Error", MB_OK);
                break;
            case D3DERR_INVALIDCALL:
                MessageBox(NULL, "Invalid Call!", "Error", MB_OK);
                break;
            case D3DXFERR_FILENOTFOUND:
                MessageBox(NULL, "File Not Found!", "Error", MB_OK);
                break;
            case D3DXFERR_PARSEERROR:
                MessageBox(NULL, "Parse Error!", "Error", MB_OK);
                break;
            default:
                MessageBox(NULL, "No Mesh!", "Error", MB_OK);
                break;
        }
        return;
    }

    // Extract the material properties and texture names from the pD3DXMtrlBuffer
    D3DXMATERIAL *d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer -> GetBufferPointer();
    // Create new textures and materials in memory.
    meshMaterials_ = new D3DMATERIAL9[numMaterials_];
    meshTextures_  = new LPDIRECT3DTEXTURE9[numMaterials_];

    for (DWORD i(0); i < numMaterials_; ++i) {
        // Copy the material
        meshMaterials_[i] = d3dxMaterials[i].MatD3D;

        // Set the ambient color for the material (D3DX does not do this)
        meshMaterials_[i].Ambient = meshMaterials_[i].Diffuse;

        meshTextures_[i] = NULL;
        if (d3dxMaterials[i].pTextureFilename != NULL && lstrlen(d3dxMaterials[i].pTextureFilename) > 0 ) {
            // Create the texture
            string str(path);
            string fName(d3dxMaterials[i].pTextureFilename);
            size_t marker = fName.find_last_of("/");
            if(marker==string::npos)
                marker = fName.find_last_of("\\");
            if(marker!=string::npos) {
                ++marker;
                fName = fName.substr(marker,fName.length()-marker);
            }
            str+=fName;
            if (FAILED(D3DXCreateTextureFromFile(WindowsPlatformTask::getInstancePtr()->getDevice(), str.c_str(), &meshTextures_[i]))) {
                MessageBox(NULL, "Cannot find texture map file", "Load Mesh", MB_OK);
                return;
            }
        }
    }

    // Done with the material buffer
    pD3DXMtrlBuffer -> Release();

    // calculate boundaries

    D3DXVECTOR3 min, max;

    BYTE* pData = 0;

    mesh_->LockVertexBuffer(0, (LPVOID*)&pData);

    D3DXComputeBoundingBox((D3DXVECTOR3*)pData, mesh_->GetNumVertices(), mesh_->GetNumBytesPerVertex(), &min, &max);

    mesh_->UnlockVertexBuffer();

    min_ = Vector3(min.x, min.y, min.z);
    max_ = Vector3(max.x, max.y, max.z);
}