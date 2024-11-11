cmake_minimum_required(VERSION 3.10)
project(Ficha2)

set(CMAKE_C_STANDARD 99)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(/opt/homebrew/include)

add_executable(Ficha2 main.c form.c
        DBForms.h
        DBForms.c
)

target_link_libraries(Ficha2 OpenGL::GL GLUT::GLUT)