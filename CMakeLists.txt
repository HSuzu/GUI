cmake_minimum_required(VERSION 3.5)

project(UserInterface LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(UserInterface main.cpp)
target_link_libraries(UserInterface
    PRIVATE
        gui
)
