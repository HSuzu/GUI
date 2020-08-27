#include <iostream>
#include <functional>
#include <string>

#include <Window.h>
#include <Renderer.h>

#include <utils/Thread.h>

int main()
{
    Thread::Task::initTaskBuffer();
    Thread::alias("main");

    Window window(640, 480, "Title");
    Renderer::OpenGL renderer;

//    GUI::Square square(0,0,100,100);
//    square.backgroundColor("#0110031");

//    renderer << square;

    while(window.isOpen())
    {
        renderer.clear();

//        square.setPosition(10,10);

        renderer.draw();

        window.updateBuffers();
        window.pollEvents();
        Thread::Task::processAll();
    }

    return 0;
}
