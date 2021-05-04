/***************************************************************************************
*	Title: MeshD3DComponent.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef MESH_D3D_COMPONENT
#define MESH_D3D_COMPONENT

#include "../Renderer/Mesh/MeshD3D.h"
#include "../../Framework/GameObjects/Components/MeshComponent.h"

class MeshD3DComponent : public MeshComponent<MeshD3D> {
    public:
		explicit MeshD3DComponent(GameObject* pOwner) : MeshComponent(pOwner) {
        }
        virtual ~MeshD3DComponent() {}

		static ComponentId getId()	{
            return COMPONENT_ID_MESH;
        }

        virtual void handleEvent(Event* pEvent);
};

#endif // MESH_D3D_COMPONENT