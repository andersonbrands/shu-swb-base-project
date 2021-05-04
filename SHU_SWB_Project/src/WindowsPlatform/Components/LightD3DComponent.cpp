/***************************************************************************************
*	Title: LightD3DComponent.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#include "LightD3DComponent.h"

#include "../../Framework/EventManager/Event.h"
#include "../WindowsPlatformTask.h"
#include "../../Framework/GameObjects/Components/TransformComponent.h"
#include "../../Framework/GameObjects/GameObject.h"
#include "../../Framework/EventManager/EventManager.h"


LightD3DComponent::LightD3DComponent(GameObject* pOwner) : Component(pOwner), enabled_(false) {
	ZeroMemory(&light_, sizeof(D3DLIGHT9));
}
LightD3DComponent::~LightD3DComponent() {
    
}

void LightD3DComponent::handleEvent(Event* pEvent) {
    switch (pEvent->getID()) {
        case RENDER_EVENT: {
            TransformComponent* transformComp = component_cast<TransformComponent>(getOwner());
            assert(transformComp);
            const Transform& tr = transformComp->getTransform();

			light_.Position.x = tr.getTranslation().getX();
            light_.Position.y = tr.getTranslation().getY();
            light_.Position.z = tr.getTranslation().getZ();

            assert(WindowsPlatformTask::getInstancePtr());
            WindowsPlatformTask::getInstancePtr()->getDevice()->SetLight(index_, &light_);
        }
        break;

        default:
            break;
    }
}

void LightD3DComponent::enable(bool enable) {
    if (enabled_ != enable) {
        enabled_ = enable;

        assert(WindowsPlatformTask::getInstancePtr());
        WindowsPlatformTask::getInstancePtr()->getDevice()->LightEnable(index_, enabled_);

        if (enabled_) {
            attachEvent(RENDER_EVENT, *this);
        } else {
            detachEvent(RENDER_EVENT, *this);
        }
    }
}
