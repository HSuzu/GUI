#include <iostream>
#include <functional>
#include <string>

#include <openGL/Window.h>
#include <openGL/OpenGLRenderer.h>
#include <gui/base_objects/Square.h>

#include <utils/Thread.h>

int main()
{

    Thread::Task::initTaskBuffer();
    Thread::alias("main");

    Window window(640, 480, "Title");
    Renderer::OpenGL renderer;

    GUI::Square square({0.0f, 0.0f},{100.0f,100.0f});
    square.backgroundColor("#0110031");

    renderer << square;

    while(window.isOpen())
    {
        renderer.clear();

        square.position(10,10);

        renderer.draw();

        window.updateBuffers();
        window.pollEvents();
        Thread::Task::processAll();
    }

    return 0;
}
