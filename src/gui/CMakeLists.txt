add_subdirectory(vendor)
add_subdirectory(openGL)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vendor)

# Interface lib (Include this one)
add_library(gui STATIC
# headers
    Renderer.h
    base_objects/Square.h

# sources
    base_objects/Square.cpp
)

target_include_directories(gui INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor
)

target_link_libraries(gui INTERFACE
    openGLRenderer
    utils

# vendor
    stb_image
    imgui
)

