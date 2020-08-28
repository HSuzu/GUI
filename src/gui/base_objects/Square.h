#ifndef SQUARE_H
#define SQUARE_H

#include "../Renderer.h"
#include "glm/glm.hpp"

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
        void setRenderer(Renderer::OpenGL *renderer) override;
    };

}

#endif // SQUARE_H
