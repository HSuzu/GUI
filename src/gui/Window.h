#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GLDebug.h"

class Window
{
private:
    GLFWwindow* _window;
public:
    Window(int width, int height, const char *title);
    ~Window();

    /* void func(GLFWwindow* window, int width, int height) */
    void setResizeCallback(void(*callback)(GLFWwindow *, int, int)) const;
    void makeContextCurrent() const;
    void setRefreshInterval(int n_screen_update) const;
    void updateBuffers() const;
    void pollEvents() const;

    bool isOpen() const;

    GLFWwindow *glWindow();
};

#endif // WINDOW_H
