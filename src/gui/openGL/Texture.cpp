#include "Texture.h"

#include "stb_image/stb_image.h"

Texture::Texture(const char *path) :
    SingletonFile<Texture>(path),
    _rendererID(0),
    _localBuffer(nullptr),
    _width(0), _height(0), _BPP(0)
{
    stbi_set_flip_vertically_on_load(1);
    _localBuffer = stbi_load(path, &_width, &_height, &_BPP, 4);

    GLCall(glGenTextures(1, &_rendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, _rendererID));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,_width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _localBuffer));

    if(_localBuffer) {
        stbi_image_free(_localBuffer);
        _localBuffer = nullptr;
    }
}

Texture::~Texture() {
    if(_localBuffer)
        stbi_image_free(_localBuffer);

    GLCall(glDeleteTextures(1, &_rendererID));
}

void Texture::bind(unsigned int slot) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, _rendererID));
}

void Texture::unbind() const {
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
