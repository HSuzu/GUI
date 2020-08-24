add_library(utils STATIC
# headers
    timespec.h
    SingletonFile.h
    Hash.h
    HashFunctions.h
# sources
    timespec.cpp
)

target_include_directories(utils INTERFACE ${CURRENT_SOURCE_DIR})
