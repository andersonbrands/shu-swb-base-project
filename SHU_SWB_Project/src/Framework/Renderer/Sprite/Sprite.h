/***************************************************************************************
*	Title: Sprite.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef SPRITE_H_
#define SPRITE_H_

#include "../Texture/Texture.h"
#include "../../Math/Vector3.h"

namespace Framework {

    class Sprite {
        public:
            enum SpriteAlign {
                TOP_LEFT,
                TOP_RIGHT,
                BOTTOM_RIGHT,
                BOTTOM_LEFT,
                CENTER,
                CENTER_LEFT,
                CENTER_TOP,
                CENTER_RIGHT,
                CENTER_BOTTOM
            };

            Sprite() {}
            virtual ~Sprite() {}

            virtual void setup(Texture *texture, SpriteAlign align, float h, float w) {
                align_ = align;
                height_ = h;
                width_ = w;

                pTexture_ = texture;

                applySettings();
            }

            virtual const Vector3 getMin() const = 0;
            virtual const Vector3 getMax() const = 0;

            virtual void render() = 0;
        private:
        protected:
            SpriteAlign align_;
            float height_;
            float width_;

            Texture *pTexture_;

            virtual void applySettings() = 0;
    };

}

#endif // SPRITE_H_
