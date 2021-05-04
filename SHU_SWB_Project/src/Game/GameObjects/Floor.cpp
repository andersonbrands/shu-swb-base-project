/***************************************************************************************
*	Title: Floor.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#include "Floor.h"

#include "../../Framework/GameObjects/Components/TransformComponent.h"
#include "../../WindowsPlatform/Components/MeshD3DComponent.h"
#include "../../Framework/Renderer/Mesh/MeshManager.h"
#include "../../Framework/GameObjects/Components/AABBColliderComponent.h"

Floor::Floor() {

}

Floor::~Floor() {

}

void Floor::setup() {
    assert(addComponent<TransformComponent>());

    TransformComponent* pTransformComp = component_cast<TransformComponent>(this);

    Transform& floor1Transform(pTransformComp->getTransform());

    floor1Transform.setTranslation(Vector3(0.0f, 0.0f, 10.0f));
    floor1Transform.setScale(Vector3(0.5f, 0.5f, 0.5f));
    floor1Transform.setRotation(Vector3(0.0f, 0.0f, 0.0f));

    assert(MeshManager::getInstancePtr());
    MeshD3D* pMeshD3D = MeshManager::getInstancePtr()->loadMesh<MeshD3D>(MESH_FLOOR_1);

    assert(addComponent<MeshD3DComponent>());
    MeshD3DComponent* pAddedMesh = component_cast<MeshD3DComponent>(this);
    pAddedMesh->setMesh(MESH_FLOOR_1);

    assert(addComponent<AABBColliderComponent>());
}

void Floor::update() {

}

