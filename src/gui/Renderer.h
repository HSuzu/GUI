#pragma once

#ifndef RENDERER_H
#define RENDERER_H

namespace GUI {
    class base_ui;
}

namespace Renderer {
    class OpenGL;
}

namespace Renderer {
    class base_renderer {
    public:
        virtual ~base_renderer() {}
        virtual void clear() const = 0;
        virtual void draw() const  = 0;
        virtual void render(GUI::base_ui &obj) = 0;

        base_renderer &operator<<(GUI::base_ui &obj) { render(obj); return *this; }
    };
}


namespace GUI {
    class base_ui {
    public:
        virtual void setRenderer(Renderer::OpenGL *renderer) = 0;
    };

}

#endif
