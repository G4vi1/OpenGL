cmake_minimum_required(VERSION 3.10)
project(hello_window)

 

add_executable(hello_window src/main.cpp src/glad.c)

target_include_directories(hello_window PRIVATE
    ${CMAKE_SOURCE_DIR}/dependencies
    ${CMAKE_SOURCE_DIR}/dependencies/GLFW/include)

target_link_libraries(hello_window PRIVATE
    ${CMAKE_SOURCE_DIR}/dependencies/GLFW/lib/libglfw3.a
    GL X11 pthread dl m)