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

namespace GUI {
    class base_ui;
}

namespace Renderer {
    class base_renderer {
    public:
        virtual void clear() const = 0;
        virtual void draw() const  = 0;
        virtual void render(GUI::base_ui &obj) = 0;

        base_renderer &operator<<(GUI::base_ui &obj) { render(obj); return *this; }
    };

    class OpenGL : public base_renderer {
    public:
        OpenGL();

        void clear() const override;
        void draw() const override;
        void render(GUI::base_ui &obj) override;

        void draw(const VertexArray &va, const IndexBuffer &ib, const Material &m) const;
    };
}


namespace GUI {
    class base_ui {
    public:
        virtual void setRenderer(Renderer::OpenGL *renderer) = 0;
    };
}

#endif
