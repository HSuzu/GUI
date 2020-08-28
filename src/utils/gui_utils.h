#pragma once

#ifndef GUI_UTILS_H
#define GUI_UTILS_H

#include "glm/glm.hpp"

namespace Utils {
char lower(const char c)
{
    if(c < 'A') return c;
    if(c <= 'Z') return c + 'a' - 'A';
    return c;
}

unsigned int hex2dec(const char *hex, const int size)
{
    unsigned int r {0};
    for(int i {0}; i < size && hex[i] != '\0'; i++)
    {
        r <<= 4; // multiply r by 16
        char h { lower(hex[i]) };

        if(h <= '9')
            r += h - '0';
        else
            r += h - 'a' + 10;
    }

    return r;
}

namespace GUI {

// format #rrggbbaa
glm::vec4 color(const char *hex)
{
    if(hex == nullptr)
        return {0.0f,0.0f,0.0f,0.0f};

    glm::vec4 r;
    r.r = hex2dec(hex+1, 2)/255.0f;
    r.g = hex2dec(hex+3, 2)/255.0f;
    r.b = hex2dec(hex+5, 2)/255.0f;

    if(hex[7] == '\0')
        r.a = 1.0f;
    else
        r.a = hex2dec(hex+7, 2)/255.0f;

    return r;
}

}
}

#endif // GUI_UTILS_H
