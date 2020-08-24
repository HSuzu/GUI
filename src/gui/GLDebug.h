#ifndef GLDEBUGMACROS_H
#define GLDEBUGMACROS_H

#include <GL/glew.h>
#include <csignal>
#include <iostream>

#define ERROUT(msg) std::cerr << (msg)

#ifdef NDEBUG
    #define DEBUGINT() ((void)0)
    #define ASSERT(x) ((void)0)
#else
    #define DEBUGINT() raise(SIGINT)
    #define ASSERT(x) if(!(x)) { DEBUGINT(); }
#endif

#ifdef NDEBUG
    #define ERRORMSG(x,msg) ((void)0)
#else
    #define ERRORMSG(x,msg) do {    \
        ERROUT(msg);                \
        exit(x);                    \
    } while(0);
#endif

#ifdef NDEBUG
    #define GLCall(x) x
#else
    #define GLCall(x) do {       \
            GLClearError();      \
            x;                   \
            ASSERT(GLLogCall(#x, __FILE__, __LINE__)); \
        } while (0)
#endif

#define GLAssertTypeSize(x,y) static_assert(sizeof(x) == sizeof(y), "")

void GLClearError();
bool GLLogCall(const char *function, const char *filename, int line);

#endif
