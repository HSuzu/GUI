include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src/gui)
include_directories(${CMAKE_SOURCE_DIR}/src/gui/vendor)

add_library(openGLRenderer STATIC
# headers
    GLDebug.h
    IndexBuffer.h
    Shader.h
    Texture.h
    VertexArray.h
    VertexBuffer.h
    VertexBufferLayout.h
    Material.h
    Window.h

# sources
    GLDebug.cpp
    IndexBuffer.cpp
    Shader.cpp
    Texture.cpp
    VertexArray.cpp
    VertexBuffer.cpp
    OpenGLRenderer.cpp
    Window.cpp
)

# Materials
file(GLOB SHADERS_FILES ${CMAKE_SOURCE_DIR}/res/shaders/*)
file(GLOB TEXTURES_FILES ${CMAKE_SOURCE_DIR}/res/textures/*)

add_library(openGLMaterials STATIC
# headers
    materials/UniformVertexColor.h

# sources
    materials/UniformVertexColor.cpp

# resources
    ${SHADERS_FILES}
    ${TEXTURES_FILES}
)

add_library(openGLObjects STATIC
# sources
    objects/Square.cpp
)

set(THREADS_PREFER_PTHREAD_FLAG ON)
set(OpenGL_GL_PREFERENCE "GLVND")

find_package(Threads    REQUIRED)
find_package(OpenGL     REQUIRED)
find_package(X11        REQUIRED)
find_package(glfw3 3.3  REQUIRED)
find_package(GLEW       REQUIRED)
find_library(MATH_LIBRARY m)

target_include_directories(openGLRenderer
PUBLIC
    ${X11_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
)

target_link_libraries(openGLRenderer INTERFACE
    Threads::Threads
    ${X11_LIBRARIES}
    ${X11_Xfixes_LIB}
    glfw
    OpenGL::GL
    ${GLEW_LIBRARIES}
    ${CMAKE_DL_LIBS}
    ${MATH_LIBRARY}

    openGLMaterials
    openGLObjects
)
