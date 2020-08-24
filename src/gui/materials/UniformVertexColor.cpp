#include "UniformVertexColor.h"

UniformVertexColor::UniformVertexColor() :
    _shader(Shader::fromFile("res/shaders/basic.glsl")),
    u_Color(_shader->getUniformLocation("u_Color")),
    u_MVP(_shader->getUniformLocation("u_MVP"))
{
    r = g = b = 0.0f;
    a = 1.0f;
}

void UniformVertexColor::color(float r_norm, float g_norm, float b_norm, float a_norm)
{
    r = r_norm;
    g = g_norm;
    b = b_norm;
    a = a_norm;
}

void UniformVertexColor::mvp(const glm::mat4 &matrix)
{
    _mvp = matrix;
}

void UniformVertexColor::bind() const
{
    _shader->bind();
}

void UniformVertexColor::unbind() const
{
    _shader->unbind();
}

void UniformVertexColor::updateUniforms() const
{
    _shader->setUniform4f(u_Color, r, g, b, a);
    _shader->setUniformMat4f(u_MVP, _mvp);
}
