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
    message("Building with FreeGLUT")

    # FreeGLUT
    set(FREEGLUT_BUILD_SHARED_LIBS 0)
    set(FREEGLUT_BUILD_STATIC_LIBS 1)
    add_subdirectory(lib/freeglut)
    if (UNIX OR MINGW)
        target_compile_options(freeglut_static PRIVATE "-Wno-all")      # Remove annoying font unused values (in CMakeList line 305)
        target_compile_options(freeglut_static PRIVATE "-Wno-pedantic") # Remove annoying ISO C does not allow extra ';' outside of a function [-Wpedantic] (in CMakeList line 308)
    endif ()
    list(APPEND INCLUDE_DIRS $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/lib/freeglut/include>)
    list(APPEND INCLUDE_LIBS freeglut_static)
    add_compile_options(-DBUILD_LIB_FREEGLUT)
endif()

if(BUILD_LIB_GLUI)
    message("Building with GLUI")

    add_subdirectory(lib/glui)
    list(APPEND INCLUDE_DIRS $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/lib/glui/include>)
    list(APPEND INCLUDE_LIBS glui)
    add_compile_options(-DBUILD_LIB_GLUI)
endif()

if(BUILD_LIB_GLM)
    message("Building with GLM")

    add_subdirectory(lib/glm)
    list(APPEND INCLUDE_DIRS $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/lib/glm/glm>)
    list(APPEND INCLUDE_LIBS glm)
    add_compile_options(-DBUILD_LIB_GLM)
endif()

# OpenGL
find_package(OpenGL REQUIRED)


add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${COMPILE_FILES})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${INCLUDE_LIBS})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})

if (UNIX OR MINGW)
    target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -pedantic)
elseif (MSVC)
    target_compile_options(${PROJECT_NAME} PUBLIC /W3)
endif ()