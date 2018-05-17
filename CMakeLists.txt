cmake_minimum_required(VERSION 3.10)
project(comp330_space_assignment)

set(CMAKE_CXX_FLAGS "-std=c++0x")

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(src)
link_directories(lib)

add_executable(comp330_space_assignment
        src/main.cpp
        src/helpers/shapes.cpp
        src/helpers/shapes.hpp
        src/helpers/SOIL.h
        src/helpers/utils.cpp
        src/helpers/utils.hpp
        src/helpers/textures.cpp
        src/helpers/textures.hpp
        src/constants.hpp
        src/entities/planets/solar_system.cpp
        src/entities/planets/solar_system.hpp
        src/entities/planets/saturn.cpp
        src/entities/planets/saturn.hpp
        src/entities/planets/planet.cpp
        src/entities/planets/planet.hpp
        src/entities/probe.cpp
        src/entities/probe.hpp)
target_link_libraries(comp330_space_assignment SOIL ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

file(COPY ./textures DESTINATION ./)
