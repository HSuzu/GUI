#include "Window.h"

Window::Window(int width, int height, const char *title): _window(nullptr) {
    /* Initialize the library */
    if (!glfwInit())
        ERRORMSG(0x501, "[Window] GLFW init fail.\n");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    _window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!_window)
    {
        glfwTerminate();
        ERRORMSG(0x502, "[Window] GLFW failed to create a window.\n");
    }

    makeContextCurrent();

    if(glewInit() != GLEW_OK)
        ERRORMSG(0x503, "[Window] Fail to init GLEW.\n");

    std::cout << "OpenGL version " << glGetString(GL_VERSION) << std::endl;

    setRefreshInterval(1);


    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

Window::~Window()
{
    glfwTerminate();
}

void Window::setResizeCallback(void(*callback)(GLFWwindow*, int, int)) const
{
    glfwSetFramebufferSizeCallback(_window, callback);
}

void Window::makeContextCurrent() const
{
    /* Make the window's context current */
    glfwMakeContextCurrent(_window);
}

void Window::setRefreshInterval(int n_screen_update) const
{
    /* Limit the frame rate */
    glfwSwapInterval(n_screen_update);
}

void Window::updateBuffers() const
{
    /* Swap front and back buffers */
    glfwSwapBuffers(_window);
}

void Window::pollEvents() const
{
    /* Poll for and process events */
    glfwPollEvents();
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(_window);
}

GLFWwindow *Window::glWindow()
{
    return _window;
}
