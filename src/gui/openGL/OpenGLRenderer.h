#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GLDebug.h"

#include "../Renderer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Material.h"

namespace Renderer {

    class OpenGL : public base_renderer {
    public:
        OpenGL();
        ~OpenGL() {};

        void clear() const override;
        void draw() const override;
        void render(GUI::base_ui &obj) override;

        void draw(const VertexArray &va, const IndexBuffer &ib, const Material &m) const;
    };

}

#endif // OPENGLRENDERER_H
