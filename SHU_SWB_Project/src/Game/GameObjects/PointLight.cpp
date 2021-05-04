/***************************************************************************************
*	Title: PointLight.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#include "PointLight.h"

#include "../../Framework/GameObjects/Components/TransformComponent.h"
#include "../../WindowsPlatform/Components/MeshD3DComponent.h"
#include "../../Framework/Renderer/Mesh/MeshManager.h"
#include "../../WindowsPlatform/Components/LightD3DComponent.h"

PointLight::PointLight() {

}

PointLight::~PointLight() {

}

void PointLight::setup() {
    addComponent<TransformComponent>();
    Transform& transform = component_cast<TransformComponent>(this)->getTransform();
    transform.setTranslation(Vector3(0,15,-15));
    transform.setScale(Vector3(0.1f, 0.1f, 0.1f));

    addComponent<LightD3DComponent>();

    LightD3DComponent* pLightComp = component_cast<LightD3DComponent>(this);
    pLightComp->setIndex(0);
    pLightComp->setType(D3DLIGHT_POINT);
    pLightComp->setDiffuseColor(ColorARGB(1.0f, 0.75f, 0.75f, 0.75f));
    pLightComp->setDirection(Vector3(0, -1, 1));
    pLightComp->setConstantAttenuation(0.7f);
    pLightComp->setRange(200.0f);
    pLightComp->setPhi(3.14f);
    pLightComp->setTheta(1.75f);
    pLightComp->setFalloff(0);

    pLightComp->enable(true);

    MeshManager::getInstancePtr()->loadMesh<MeshD3D>(MESH_SPHERE_FLIPPED_N);

    assert(addComponent<MeshD3DComponent>());
    component_cast<MeshD3DComponent>(this)->setMesh(MESH_SPHERE_FLIPPED_N);
}

void PointLight::update() {

}

