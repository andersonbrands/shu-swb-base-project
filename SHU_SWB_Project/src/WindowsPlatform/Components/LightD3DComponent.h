/***************************************************************************************
*	Title: LightD3DComponent.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef LIGHT_D3D_COMPONENT_H_
#define LIGHT_D3D_COMPONENT_H_

#include <d3dx9.h>
#include "../../Framework/Utilities/Color.h"
#include "../../Framework/Math/Vector3.h"
#include "../../Framework/GameObjects/Component.h"
#include "../../Framework/GameObjects/ComponentId.h"
#include "../../Framework/EventManager/EventHandler.h"

using namespace Framework;

class LightD3DComponent : public Component, public EventHandler {
    public:
        explicit LightD3DComponent(GameObject* pOwner);
        ~LightD3DComponent();

		static ComponentId getId()	{
            return COMPONENT_ID_LIGHT;
        }

        virtual void handleEvent(Event* pEvent);

        void enable(bool);

        void setType(D3DLIGHTTYPE type) {
            light_.Type = type;
        }
        void setDiffuseColor(ColorARGB color) {
            light_.Diffuse.a = color.a;
            light_.Diffuse.r = color.r;
            light_.Diffuse.g = color.g;
            light_.Diffuse.b = color.b;
        }
        void setAmbientColor(ColorARGB color) {
            light_.Ambient.a = color.a;
            light_.Ambient.r = color.r;
            light_.Ambient.g = color.g;
            light_.Ambient.b = color.b;
        }
        void setSpecularColor(ColorARGB color) {
            light_.Specular.a = color.a;
            light_.Specular.r = color.r;
            light_.Specular.g = color.g;
            light_.Specular.b = color.b;
        }

        void setDirection(Vector3 direction) {
			light_.Direction.x = direction.getX();
            light_.Direction.y = direction.getY();
            light_.Direction.z = direction.getZ();
        }

        void setRange(float range) {
            light_.Range = range;
        }
        void setFalloff(float falloff) {
            light_.Falloff = falloff;
        }
        void setConstantAttenuation(float constantAttenuation) {
            light_.Attenuation0 = constantAttenuation;
        }
        void setLinearAttenuation(float linearAttenuation) {
            light_.Attenuation1 = linearAttenuation;
        }
        void setQuadraticAttenuation(float quadraticAttenuation) {
            light_.Attenuation2 = quadraticAttenuation;
        }
        void setTheta(float theta) {
			light_.Theta = theta;
		}
        void setPhi(float phi) {
			light_.Phi = phi;
		}
		void setIndex(unsigned int index) {
			index_ = index;
		}

		const D3DLIGHT9& getLight() {
			return light_;
		}


    private:
        D3DLIGHT9 light_;
        unsigned int index_;
		bool enabled_;
};

#endif // LIGHT_D3D_COMPONENT_H_
