/***************************************************************************************
*	Title: Dice.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#include "Dice.h"

#include "../../Framework/GameObjects/Components/TransformComponent.h"
#include "../../WindowsPlatform/Components/MeshD3DComponent.h"
#include "../../Framework/Renderer/Mesh/MeshManager.h"
#include "../../Framework/GameObjects/Components/AABBColliderComponent.h"

Dice::Dice() {

}

Dice::~Dice() {

}

void Dice::setup() {
    assert(addComponent<TransformComponent>());

    TransformComponent* pTransformComp(component_cast<TransformComponent>(this));

    Transform& tr(pTransformComp->getTransform());

    tr.setTranslation(Vector3(0.0f, 1.0f, 0.0f));
    tr.setScale(Vector3(0.1f));
    tr.setRotation(Vector3(0.0f));

    assert(MeshManager::getInstancePtr());

    MeshManager::getInstancePtr()->loadMesh<MeshD3D>(MESH_DICE);

    assert(addComponent<MeshD3DComponent>());
    component_cast<MeshD3DComponent>(this)->setMesh(MESH_DICE);

    assert(addComponent<AABBColliderComponent>());
}

void Dice::update() {
    TransformComponent* pTransformComp = component_cast<TransformComponent>(this);
    Transform& diceTransform(pTransformComp->getTransform());

    diceTransform.rotate(Vector3(0, 0.015f, 0));
}

