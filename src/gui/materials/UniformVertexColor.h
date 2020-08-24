#pragma once

#ifndef UNIFORMVERTEXCOLOR_H
#define UNIFORMVERTEXCOLOR_H

#include "GLDebug.h"
#include "Shader.h"
#include "Material.h"
#include "glm/glm.hpp"


class UniformVertexColor : public Material
{
private:
    float r,g,b,a;
    glm::mat4 _mvp;

    Shader::ptr _shader;
    Shader::Uniform u_Color;
    Shader::Uniform u_MVP;
public:
    UniformVertexColor();

    /* Set color with normalized values (inside interval [0.0f, 1.0f] ) */
    void color(float r_norm, float g_norm, float b_norm, float a_norm);

    void mvp(const glm::mat4 &matrix);

    void bind() const final;
    void unbind() const final;
    void updateUniforms() const final;
};

#endif // UNIFORMVERTEXCOLOR_H
