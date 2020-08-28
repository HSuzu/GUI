#include "OpenGLRenderer.h"

namespace Renderer {

OpenGL::OpenGL() {}

void OpenGL::render(GUI::base_ui &obj)
{
    obj.setRenderer(this);
}

void OpenGL::clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void OpenGL::draw() const
{

}

void OpenGL::draw(const VertexArray &va, const IndexBuffer &ib, const Material &m) const
{
    m.bind();
    va.bind();
    ib.bind();

    m.updateUniforms();

    GLCall(glDrawElements(GL_TRIANGLES, ib.count(), GL_UNSIGNED_INT, nullptr));
}

}
