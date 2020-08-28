#include "VertexArray.h"

extern "C" {
#include <stdint.h>
}

VertexArray::VertexArray() {
    GLCall(glGenVertexArrays(1, &_rendererID));
}

VertexArray::~VertexArray() {
    GLCall(glDeleteVertexArrays(1, &_rendererID));
}

void VertexArray::addBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout)
{
    bind();
    vb.bind();

    const auto & elements = layout.getElements();
    uintptr_t offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++) {
        const auto &element = elements[i];

        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.stride(), (void *)offset));

        offset += element.count * element.sizeOfType();
    }
}

void VertexArray::bind() const {
    GLCall(glBindVertexArray(_rendererID));
}

void VertexArray::unbind() const {
    GLCall(glBindVertexArray(0));
}
