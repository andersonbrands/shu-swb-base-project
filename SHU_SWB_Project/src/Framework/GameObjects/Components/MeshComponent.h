/***************************************************************************************
*	Title: MeshComponent.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef MESH_COMPONENT_H_
#define MESH_COMPONENT_H_

#include "../Component.h"
#include "../ComponentId.h"
#include "../../EventManager/EventHandler.h"
#include "../../EventManager/EventManager.h"
#include "../../Renderer/Mesh/MeshId.h"
#include "../../Renderer/Mesh/MeshManager.h"

namespace Framework {

    template <class T>
    class MeshComponent : public Component, public EventHandler {
        protected:
            T* mesh_;
        public:
            explicit MeshComponent(GameObject* pOwner) : Component(pOwner), mesh_(nullptr) {
            }
            virtual ~MeshComponent() {}

            static ComponentId getId()	{
                return COMPONENT_ID_MESH;
            }

            void setMesh(const MeshIdAndName &meshIdAndName) {
                assert(MeshManager::getInstancePtr());
                mesh_ = dynamic_cast<T*>(MeshManager::getInstancePtr()->getMesh(meshIdAndName));

                assert(mesh_);

                attachEvent(RENDER_EVENT, *this);
            }

            const Vector3 getMin() const {
                return mesh_->getMin();
            }

            const Vector3 getMax() const {
                return mesh_->getMax();
            }

            virtual void handleEvent(Event* pEvent) = 0;
    };

}
#endif // MESH_COMPONENT_H_