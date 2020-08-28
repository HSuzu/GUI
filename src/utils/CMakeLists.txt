add_library(utils STATIC
# headers
    timespec.h
    SingletonFile.h
    Hash.h
    HashFunctions.h
    gui_utils.h

# sources
    timespec.cpp
)

add_library(threads STATIC
# headers
    Thread.h
    Mutex.h

# sources
    Thread.cpp
)

find_package(Threads    REQUIRED)
target_link_libraries(threads INTERFACE
    Threads::Threads # Thread.cpp
)

target_include_directories(utils INTERFACE ${CURRENT_SOURCE_DIR})
target_link_libraries(utils INTERFACE
    threads
)
