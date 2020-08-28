#pragma once

#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GLDebug.h"

class IndexBuffer {
private:
    unsigned int _rendererID;
    unsigned int _count;
public:
    IndexBuffer(const unsigned int *data, unsigned int count);
    virtual ~IndexBuffer();

    void bind() const;
    void unbind() const;

    unsigned int count() const { return _count; }
};

#endif // INDEX_BUFFER_H
