/***************************************************************************************
*	Title: MouseIndicator.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#include "MouseIndicator.h"

#include "../../Framework/GameObjects/Components/TransformComponent.h"
#include "../../WindowsPlatform/Components/MeshD3DComponent.h"
#include "../../Framework/Renderer/Mesh/MeshManager.h"
#include "../../Framework/GameObjects/Components/AABBColliderComponent.h"

MouseIndicator::MouseIndicator() {

}

MouseIndicator::~MouseIndicator() {

}

void MouseIndicator::setup() {
    addComponent<TransformComponent>();
    Transform& transform = component_cast<TransformComponent>(this)->getTransform();
    transform.setTranslation(Vector3(0,0,0));
    transform.setScale(Vector3(0.1f, 0.1f, 0.1f));

    MeshManager::getInstancePtr()->loadMesh<MeshD3D>(MESH_SPHERE);

    assert(addComponent<MeshD3DComponent>());
    component_cast<MeshD3DComponent>(this)->setMesh(MESH_SPHERE);

    addComponent<AABBColliderComponent>();
}

void MouseIndicator::update() {

}
