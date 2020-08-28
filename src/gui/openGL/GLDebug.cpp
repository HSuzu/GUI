#include "GLDebug.h"
#include <iostream>

void GLClearError()
{
    while(glGetError());
}

bool GLLogCall(const char *function, const char *filename, int line)
{
    bool ret = true;
    while(GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (0x" << std::hex << error << std::dec << "): "
                  << function << " in " << filename << ":" << line << std::endl;
        ret = false;
    }

    return ret;
}
