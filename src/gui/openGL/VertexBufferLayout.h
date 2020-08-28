#ifndef VERTEX_BUFFER_LAYOUT_H
#define VERTEX_BUFFER_LAYOUT_H

#include <GL/glew.h>
#include <vector>

#include "GLDebug.h"

struct VertexBufferElement {
    unsigned int type;          /* Type of the attribute */
    unsigned int count;         /* Number of elements inside the attribute */
    unsigned char normalized;   /* Normalized indicates if the data shall be mapped to the range [-1,1] (signed) or [0,1] (unsigned) */

    static unsigned int sizeOfType(unsigned int type) {
        switch(type) {
            case GL_FLOAT:          return sizeof(GLfloat);
            case GL_UNSIGNED_INT:   return sizeof(GLuint);
            case GL_UNSIGNED_BYTE:  return sizeof(GLubyte);
            default:
                ASSERT(false);
                return 0;
        }
    }

    unsigned int sizeOfType() const { return sizeOfType(type); }
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> _elements;
    unsigned int _stride;
public:
    VertexBufferLayout() : _stride(0) {}
    ~VertexBufferLayout() {}

    const std::vector<VertexBufferElement> &getElements() const { return _elements; }
    unsigned int stride() const { return _stride; }
    
    template<typename T>
    void push(unsigned int count, unsigned char normalized = GL_FALSE) {
        ASSERT(false);
    }
};

template<>
inline void VertexBufferLayout::push<float>(
        unsigned int  count,
        unsigned char normalized
    )
{
    GLAssertTypeSize(float, GLfloat);

    VertexBufferElement elem;
    elem.type = GL_FLOAT;
    elem.count = count;
    elem.normalized = normalized;

    _elements.push_back(elem);
    _stride += count * elem.sizeOfType();
}

template<>
inline void VertexBufferLayout::push<unsigned int> (
        unsigned int  count,
        unsigned char normalized
    )
{
    GLAssertTypeSize(unsigned int, GLuint);

    VertexBufferElement elem;
    elem.type = GL_UNSIGNED_INT;
    elem.count = count;
    elem.normalized = normalized;

    _elements.push_back(elem);
    _stride += count * elem.sizeOfType();
}

template<>
inline void VertexBufferLayout::push<unsigned char>(
        unsigned int  count,
        unsigned char normalized
    )
{
    GLAssertTypeSize(unsigned char, GLubyte);

    VertexBufferElement elem;
    elem.type = GL_UNSIGNED_BYTE;
    elem.count = count;
    elem.normalized = normalized;

    _elements.push_back(elem);
    _stride += count * elem.sizeOfType();
}

#endif // VERTEX_BUFFER_LAYOUT_H