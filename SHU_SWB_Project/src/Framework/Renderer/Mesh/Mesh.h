/***************************************************************************************
*	Title: Mesh.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef MESH_H_
#define MESH_H_

#include <string>
#include "../../../Framework/Math/Vector3.h"

using namespace std;
namespace Framework {

    class Mesh {
        protected:
            virtual void load(const string &path, const string &filename) = 0;

            Vector3 min_;
            Vector3 max_;
        public:
            Mesh() { }
            virtual ~Mesh() {}

            virtual void render() = 0;

            const Vector3 getMin() const {
                return min_;
            }

            const Vector3 getMax() const {
                return max_;
            }
    };

}
#endif // MESH_H_
