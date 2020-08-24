#pragma once

#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GLDebug.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Material.h"

class Renderer {
public:
    Renderer();

    void clear() const;
    void draw(const VertexArray &va, const IndexBuffer &ib, const Material &m) const;
};

#endif
