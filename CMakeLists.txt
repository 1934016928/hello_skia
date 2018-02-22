cmake_minimum_required(VERSION 3.9)
project(HelloSDL)

set(CMAKE_CXX_STANDARD 11)

set(SKIA /home/var_rain/files/skia)

include_directories(
        ${SKIA}/include
        ${SKIA}/include/andriod
        ${SKIA}/include/atlastext
        ${SKIA}/include/c
        ${SKIA}/include/codec
        ${SKIA}/include/config
        ${SKIA}/include/core
        ${SKIA}/include/effects
        ${SKIA}/include/encode
        ${SKIA}/include/gpu
        ${SKIA}/include/gpu/gl
        ${SKIA}/include/gpu/mock
        ${SKIA}/include/gpu/mtl
        ${SKIA}/include/gpu/vk
        ${SKIA}/include/pathops
        ${SKIA}/include/ports
        ${SKIA}/include/private
        ${SKIA}/include/svg
        ${SKIA}/include/utils
        ${SKIA}/include/views
)

link_libraries(
        SDL2
        ${SKIA}/out/Shared/libskia.so
)

add_executable(HelloSDL main.cpp main.cpp)