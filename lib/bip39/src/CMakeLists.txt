cmake_minimum_required(VERSION 3.2)
project(bip39 C CXX)

include_directories(lib/PicoSHA2)

set(SOURCE_FILES
        bip39.cpp
        util.cpp
)

add_library(${PROJECT_NAME} SHARED STATIC ${SOURCE_FILES})

set(bip39_build_include_dirs
        ../../..
        ../../../include
)
include_directories(${bip39_build_include_dirs})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${bip39_build_include_dirs}
)
