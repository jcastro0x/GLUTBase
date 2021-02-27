# MIT License

# Copyright (c) 2021 jcastro0x

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required(VERSION 3.17)
project(GLUTBase)

set(CMAKE_CXX_STANDARD 17)

# setup version numbers
# TODO: Update these for each release!
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)
set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

list(APPEND COMPILE_FILES
    src/main.cpp
)

if(WIN32)
    list(APPEND COMPILE_FILES src/res/one.rc)
endif()

option(BUILD_LIB_FREEGLUT "Build with FreeGLUT." ON)
option(BUILD_LIB_GLUI "Build with GLUI." ON)
option(BUILD_LIB_GLM "Build with GLM." ON)


if(BUILD_LIB_FREEGLUT)
    OPTION(FREEGLUT_BUILD_STATIC_LIBS "Build FreeGLUT static library." ON)
    OPTION(FREEGLUT_BUILD_SHARED_LIBS "Build FreeGLUT shared library." OFF)
    option(FREEGLUT_BUILD_DEMOS "Build FreeGLUT demos." OFF)
    
    add_subdirectory(lib/freeglut)
    if (UNIX OR MINGW)
        target_compile_options(freeglut_static PRIVATE "-Wno-all")      # Remove annoying font unused values (in CMakeList line 305)
        target_compile_options(freeglut_static PRIVATE "-Wno-pedantic") # Remove annoying ISO C does not allow extra ';' outside of a function [-Wpedantic] (in CMakeList line 308)
    endif ()
    list(APPEND INCLUDE_DIRS $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/lib/freeglut/include>)
    list(APPEND INCLUDE_LIBS freeglut_static)
    add_compile_definitions(BUILD_LIB_FREEGLUT)
endif()

if(BUILD_LIB_GLUI)
    add_subdirectory(lib/glui)
    list(APPEND INCLUDE_DIRS $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/lib/glui/include>)
    list(APPEND INCLUDE_LIBS glui)
    add_compile_definitions(BUILD_LIB_GLUI)
endif()

if(BUILD_LIB_GLM)
    add_subdirectory(lib/glm)
    list(APPEND INCLUDE_DIRS $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/lib/glm/glm>)
    list(APPEND INCLUDE_LIBS glm)
    add_compile_definitions(BUILD_LIB_GLM)
endif()

# OpenGL
find_package(OpenGL REQUIRED)


if(WIN32)
    set(BUILD_OPTIONS WIN32)
elseif(UNIX AND APPLE)
    set(BUILD_OPTIONS MACOSX_BUNDLE)
endif()


add_executable(${PROJECT_NAME} ${BUILD_OPTIONS} ${COMPILE_FILES})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${INCLUDE_LIBS})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})

if (UNIX OR MINGW)
    target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -pedantic)
elseif (MSVC)
    target_compile_options(${PROJECT_NAME} PUBLIC /W3)
endif ()