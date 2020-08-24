#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

class VertexBuffer {
private:
    unsigned int _rendererID;
public:
    VertexBuffer(const void *data, unsigned int size);
    virtual ~VertexBuffer();

    void bind() const;
    void unbind() const;
};

#endif // VERTEX_BUFFER_H