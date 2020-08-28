#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(
    const unsigned int * data,
    unsigned int count
) : _count(count)
{ 
    /* Data type */
    using data_t = unsigned int;
    /* Check if we have compatible GL type and Cpp type */
    ASSERT(sizeof(data_t) == sizeof(GLuint));

    GLCall(glGenBuffers(1, &_rendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID));
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(data_t), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    GLCall(glDeleteBuffers(1, &_rendererID));
}

void IndexBuffer::bind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID));
}

void IndexBuffer::unbind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
