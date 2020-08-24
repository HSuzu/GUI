add_subdirectory(vendor)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vendor)

# Interface lib (Include this one)
add_library(gui INTERFACE)
target_link_libraries(gui INTERFACE
    materials
    gui_base
)

target_include_directories(gui INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor
)

# Base
add_library(gui_base STATIC
# headers
    GLDebug.h
    IndexBuffer.h
    Renderer.h
    Shader.h
    Texture.h
    VertexArray.h
    VertexBuffer.h
    VertexBufferLayout.h
    Window.h
    Material.h

# sources
    GLDebug.cpp
    IndexBuffer.cpp
    Renderer.cpp
    Shader.cpp
    Texture.cpp
    VertexArray.cpp
    VertexBuffer.cpp
    Window.cpp
)

# Materials
file(GLOB SHADERS_FILES ../../res/shaders/*)
file(GLOB TEXTURES_FILES ../../res/textures/*)

add_library(materials STATIC
# headers
    materials/UniformVertexColor.h

# sources
    materials/UniformVertexColor.cpp

# resources
    ${SHADERS_FILES}
    ${TEXTURES_FILES}
)


set(THREADS_PREFER_PTHREAD_FLAG ON)
set(OpenGL_GL_PREFERENCE "GLVND")

find_package(Threads    REQUIRED)
find_package(OpenGL     REQUIRED)
find_package(X11        REQUIRED)
find_package(glfw3 3.3  REQUIRED)
find_package(GLEW       REQUIRED)
find_library(MATH_LIBRARY m)


target_include_directories(gui_base
PUBLIC
    ${X11_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor
)

target_link_libraries(gui_base INTERFACE
    Threads::Threads
    ${X11_LIBRARIES}
    ${X11_Xfixes_LIB}
    glfw
    OpenGL::GL
    ${GLEW_LIBRARIES}
    ${CMAKE_DL_LIBS}
    ${MATH_LIBRARY}

# vendor
    stb_image
    imgui
)

