cmake_minimum_required(VERSION 3.10)
project(hello_window)

 

add_executable(hello_window
    src/main.cpp
    src/glad.c
    src/triangle_mesh.cpp
)

target_include_directories(hello_window PRIVATE
    ${CMAKE_SOURCE_DIR}/dependencies
    ${CMAKE_SOURCE_DIR}/dependencies/GLFW/include)

target_link_libraries(hello_window PRIVATE
    ${CMAKE_SOURCE_DIR}/dependencies/GLFW/lib/libglfw3.a
    GL X11 pthread dl m)

# O programa é executado a partir de build/, então os arquivos GLSL são copiados para lá.
file(COPY ${CMAKE_SOURCE_DIR}/src/shaders DESTINATION ${CMAKE_BINARY_DIR})
