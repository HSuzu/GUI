#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <utility>

#include "utils/SingletonFile.h"
#include "GLDebug.h"

class Texture : public SingletonFile<Texture>
{
friend SingletonFile<Texture>;
private:
    unsigned int _rendererID;
    unsigned char *_localBuffer;
    int _width, _height, _BPP;

    Texture(const char *path);
public:
    ~Texture();

    void bind(unsigned int slot = 0) const;
    void unbind() const;

    inline int width() const { return _width; }
    inline int height() const { return _height; }
};

#endif // TEXTURE_H
