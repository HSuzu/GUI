#include "Renderer.h"

Renderer::Renderer() {}

void Renderer::clear() const {
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::draw(const VertexArray &va, const IndexBuffer &ib, const Material &m) const
{
    m.bind();
    va.bind();
    ib.bind();

    m.updateUniforms();

    GLCall(glDrawElements(GL_TRIANGLES, ib.count(), GL_UNSIGNED_INT, nullptr));
}
