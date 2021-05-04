/***************************************************************************************
*	Title: UnorderedMapContainer.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef UNORDERED_MAP_CONTAINER_H_
#define UNORDERED_MAP_CONTAINER_H_

#include <unordered_map>
#include <cassert>

using namespace std;

namespace Framework {

    template <typename ObjectId, typename Object>
    class UnorderedMapContainer {
        private:
            typedef tr1::unordered_map<ObjectId, Object*>	ObjectMap;
            typedef typename ObjectMap::iterator					ObjectMapIterator;

            ObjectMap objects_;

            void releaseObjs() {
                for (auto iter = objects_.begin(); iter != objects_.end(); ++iter) {
                    Object* pObject = iter->second;
                    if (pObject) {
                        delete pObject;
                        pObject = nullptr;
                    }
                }
            }

        public:
            UnorderedMapContainer() {}

            virtual ~UnorderedMapContainer() {
                releaseObjs();
            }

            void clear() {
                releaseObjs();
                objects_.clear();
            }

            template <class T>
            T* add(ObjectId id) {
                T* pNewObject(nullptr);

                bool added(false);

                ObjectMapIterator iter = objects_.find(id);
                if (iter == objects_.end()) {
                    pNewObject = new T();
                    if (pNewObject) {
                        pair<ObjectId, Object*> newObject(id, pNewObject);
                        pair<ObjectMapIterator, bool> addedIter = objects_.insert(newObject);

                        added = addedIter.second;
                    }
                }

                if (added) {
                    return pNewObject;
                } else {
                    return nullptr;
                }

            }


            Object* getObject(const ObjectId id) {
                Object* pNewObject(nullptr);

                ObjectMapIterator iter = objects_.find(id);

                if (iter != objects_.end()) {
                    pNewObject = iter->second;
                }

                return pNewObject;
            }

            void removeObject(ObjectId id) {
                ObjectMapIterator iter = objects_.find(id);

                assert(iter != objects_.end());

                Object* pObejct(iter->second);
                delete pObejct;
                pObejct = nullptr;

                objects_.erase(iter);
            }
    };

}

#endif // UNORDERED_MAP_CONTAINER_H_
