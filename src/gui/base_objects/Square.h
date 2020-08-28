#ifndef SQUARE_H
#define SQUARE_H

#include "../Renderer.h"
#include "glm/glm.hpp"
#include "utils/gui_utils.h"

namespace GUI {
    class Square : public base_ui
    {
    private:
        glm::vec2 _position;
        glm::vec2 _dimension;
        glm::vec4 _color;
    public:
        Square(
            const glm::vec2 &pos   = {0.0f,0.0f},
            const glm::vec2 &dim   = {10.0f,10.0f},
            const glm::vec4 &color = {1.0f,1.0f,1.0f,1.0f}
        );

        void setPosition(float x, float y);
        void setDimention(float w, float h);
        void setBackgroundColor(const char *color);

        void setRenderer(Renderer::OpenGL *renderer) override;

    };

}

#endif // SQUARE_H
