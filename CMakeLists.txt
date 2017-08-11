cmake_minimum_required(VERSION 3.2)
project(StealthEngine CXX)


# Flags

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")


# Output paths

set(CMAKE_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")  # executable output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")  # static libraries output directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")  # dynamic libraries output directory (unused)

message(STATUS "${PROJECT_SOURCE_DIR}/libs")
message(STATUS "GLFW_LOCATION: ${GLFW_LOCATION}")
set(GLFW_LOCATION "${PROJECT_SOURCE_DIR}/libs/glfw")
set(CMAKE_LIBRARY_PATH "${PROJECT_SOURCE_DIR}/libs")

# Input files

set(ENGINE_SOURCE_FILES
        include/application/ApplicationResult.h
        include/application/GameApplication.h
        include/application/GameClass.h
        include/application/GameConfig.h
        include/application/GLFWWindowManager.h
        include/application/WindowManager.h
        include/component/ActorComponent.h
        include/component/Component.h
        include/component/InputComponent.h
        include/component/RenderComponent.h
        include/component/SquareRenderComponent.h
        include/component/Transform.h
        include/core/EngineCore.h
        include/debug/Logger.h
        include/debug/Stream.h
        include/entity/Actor.h
        include/entity/GameObject.h
        include/factory/ComponentCreator.h
        include/factory/Factory.h
        include/factory/FactoryUtils.h
        include/factory/GameObjectCreator.h
        include/geometry/Vector2.h
        include/geometry/Vector3.cpp
        include/geometry/Vector3.h
        include/input/AxisKeyBinding.h
        include/input/ButtonState.h
        include/input/Key.h
        include/input/KeyBinding.h
        include/input/KeyData.h
        include/input/KeyEvent.h
        include/input/KeyStates.h
        include/object/Object.h
        include/renderer/Renderer.h
        include/renderer/ShaderUtils.h
        include/scene/Scene.h
        include/scene/SceneData.h
        include/scene/SceneManager.h
        include/service/InputManager.h
        include/utils/Color.h
        include/utils/ExceptionUtil.h
        include/utils/infix_iterator.h
        include/utils/MathUtil.h
        include/utils/StringUtil.h
        include/utils/TraitsUtil.h
        src/application/GameApplication.cpp
        src/application/GameClass.cpp
        src/application/GLFWWindowManager.cpp
        src/application/GLFWWindowManager.cpp
        src/application/WindowManager.cpp
        src/component/ActorComponent.cpp
        src/component/Component.cpp
        src/component/InputComponent.cpp
        src/component/RenderComponent.cpp
        src/component/SquareRenderComponent.cpp
        src/component/Transform.cpp
        src/core/EngineCore.cpp
        src/entity/Actor.cpp
        src/entity/GameObject.cpp
        src/factory/ComponentCreator.cpp
        src/factory/Factory.cpp
        src/factory/GameObjectCreator.cpp
        src/object/Object.cpp
        src/renderer/Renderer.cpp
        src/renderer/ShaderUtils.cpp
        src/scene/Scene.cpp
        src/scene/SceneData.cpp
        src/scene/SceneManager.cpp
        src/service/InputManager.cpp
        src/utils/Color.cpp
        )

set(TEST_ENGINE_SOURCE_FILES
        tests/catch.hpp
        tests/catch_with_main.hpp
        tests/testmain.cpp

        # All actual test cpp files added from here
        tests/geometry/testvec2.cpp
        tests/geometry/testvec3.cpp
        tests/utils/teststringutils.cpp
        )


# Cmake packages

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${PROJECT_SOURCE_DIR}/libs)
set(CMAKE_FIND_LIBRARY_SUFFIXES .dll .dylib .so)
set(GLEW_DIR ${PROJECT_SOURCE_DIR}/libs)

# Rendering libraries: OpenGL, GLEW, GLFW

# FindOpenGL.cmake
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIR})

message(STATUS "OpenGL found: ${OPENGL_FOUND}")
message(STATUS "OpenGL xmesa found: ${OPENGL_XMESA_FOUND}")
message(STATUS "OpenGL glu found: ${OPENGL_GLU_FOUND}")
message(STATUS "OpenGL include dir: ${OPENGL_INCLUDE_DIR}")
message(STATUS "OpenGL libraries: ${OPENGL_LIBRARIES}")
message(STATUS "OpenGL gl library: ${OPENGL_gl_LIBRARY}")

# LINUX: I installed libGLEW.so from GLEW 2.0 with some API changes, check compatibility!
# FindGLEW.cmake
find_package(GLEW REQUIRED)
# this apparently tries to build the library again and require glew-config.cmake
# (which is only in source code! /home/wing/Developer/C++/glew-2.0.0/build/cmake)
#find_package(GLEW REQUIRED PATHS ${PROJECT_SOURCE_DIR}/libs)
include_directories($(GLEW_INCLUDE_DIR))
link_directories(${GLEW_LIBRARIES})
#add_definitions(-DGLEW_STATIC)  # uncomment to use static library
#add_definitions(-DGLEW_MX)  # uncomment to use thread-safe multiple GL contexts

message(STATUS "GLEW found: ${GLEW_FOUND}")
message(STATUS "GLEW include dir: ${GLEW_INCLUDE_DIR}")
message(STATUS "GLEW libraries: ${GLEW_LIBRARIES}")

# non-static causes undefined reference to `__imp___glewGenVertexArrays' and so one
# static cause: Warning: corrupt .drectve at end of def file
# glew32s.lib(tmp/glew_static/Release/x64/glew.obj):(.text$mn+0xd): undefined reference to `__imp_wglGetProcAddress'
# find_library(GLEW glew32s ${PROJECT_SOURCE_DIR}/libs)  # static

# REFACTOR: use FIND_LIBRARY_USE_LIB64_PATHS to search automatically in lib32/lib64 as needed
# for now, make 64-bit the default (32s may be requied on Windows)

# message(STATUS "p size: ${CMAKE_SIZEOF_VOID_P}!")
# doesn't work properly (CMAKE_SIZEOF_VOID_P is empty), so just use 64-bit no matter what for now
# if you need to adapt to 32-bit, do it everywhere

# VERSION NOTES: Windows glfw3.dll is GLFW 3.2.0, libglfw.so.3.2 is GLFW 3.2.1 (API compatible)

# search different names based on OS (or rename all the libs uniformly)
#if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#    find_library(GLFW glfw.3.2 ${PROJECT_SOURCE_DIR}/libs)  # libglfw.3.2.dylib
#else((${CMAKE_SYSTEM_NAME} MATCHES "Darwin"))
#    find_library(GLFW glfw ${PROJECT_SOURCE_DIR}/libs)  # libglfw.so.3.2 or glfw3.dll
#endif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#message(STATUS "GLFW lib path: ${GLFW}")

#message(STATUS "searched in ${PROJECT_SOURCE_DIR}/libs")
#message(STATUS "version glfw: ${GLFW_VERSION}")

#set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/libs")
#set(GLFW_LOCATION libs)
find_package(GLFW)  # does not work with .a (detected in priority with MingW-w64)
#   Could not find a package configuration file provided by "GLFW" with any of
#  the following names:

#    GLFWConfig.cmake
#    glfw-config.cmake

# GLFW_FOUND
# GLFW_INCLUDE_DIR
# GLFW_LIBRARIES

message(STATUS "glfw lib path: ${GLFW}")
message(STATUS "glfw found: ${GLFW_FOUND}")
message(STATUS "glfw include dir: ${GLFW_INCLUDE_DIR}")
message(STATUS "glfw libraries: ${GLFW_LIBRARIES}")
#add_definitions(-DGLFW_DLL) (if using .a, do not use DLL (crashes as can't detect libgcc... and glfw3.dll anyway)


# Physics library: Box2D

#SET(BOX2D_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/libs/include)
#
#find_package(Box2D)
#if (BOX2D_FOUND)
#    include_directories(${BOX2D_INCLUDE_DIR})
#else (BOX2D_FOUND)
#    message(SEND_ERROR "BOX2D not found!")
#endif (BOX2D_FOUND)
#message(WARNING ${BOX2D_INCLUDE_DIR})

# Box2D: static linking
#find_library(Box2D Box2D ${PROJECT_SOURCE_DIR}/libs)
#message(STATUS "Box2D lib path: ${Box2D}")


# TODO: use INSTALL to distribute the shared libaries so the app is portable

# target

# DEBUG: in case target_include_directories does not work
include_directories(include libs/include)
include_directories(tests)  # not performant, really need to isolate target include directories

# Static library
add_library(engine ${ENGINE_SOURCE_FILES})
#target_include_directories(engine PUBLIC include PRIVATE libs/include)

add_executable(test_engine ${TEST_ENGINE_SOURCE_FILES})
# it works in UbisoftGP, try again!
#target_include_directories(engine_test PUBLIC tests)  # does not seem to work, need full path?


# http://qrikko.blogspot.fr/2016/05/cmake-and-how-to-copy-resources-during.html
# Scan through resource folder for updated files and copy if none existing or changed
message(STATUS "Copying resources from ${PROJECT_SOURCE_DIR}...")

file (GLOB_RECURSE resources "${PROJECT_SOURCE_DIR}/resources/*.*")
foreach(resource ${resources})
#    message(STATUS "getting info for ${resource}...")
    get_filename_component(filename ${resource} NAME)
    get_filename_component(dir ${resource} DIRECTORY)
    get_filename_component(dirname ${dir} NAME)
#    message(STATUS "(${resource}) filename: ${filename}, dir: ${dir}, dirname: ${dirname}")

    set (output "")

    while(NOT ${dirname} STREQUAL resources)
        get_filename_component(path_component ${dir} NAME)
        set (output "${path_component}/${output}")
        get_filename_component(dir ${dir} DIRECTORY)
        get_filename_component(dirname ${dir} NAME)
#        message(STATUS "(${dirname}) output: ${output}, path_component: ${path_component}, dir: ${dir}, dirname: ${dirname}")
    endwhile()

    set(output "${CMAKE_BINARY_DIR}/bin/resources/${output}${filename}")
#    message(STATUS "output: ${output}")

    # custom command with OUTPUT suggested by the same website does not work
    #add_custom_command(
    #COMMENT "Moving updated resource-file '${filename}'"
    #OUTPUT ${output}
    #DEPENDS ${resource}
    #COMMAND ${CMAKE_COMMAND} -E copy_if_different
    #${resource}
    #${output}
    #)
    #add_custom_target(${filename} ALL DEPENDS ${resource} ${output})

    # POST_BUILD command works
    # http://stackoverflow.com/questions/13429656/cmake-how-to-copy-contents-of-a-directory-into-build-directory-after-make
    add_custom_command(
        TARGET engine POST_BUILD COMMAND
        ${CMAKE_COMMAND} -E copy_if_different
        ${resource}
        ${output}
        COMMENT "Moving updated resource-file '${filename}'"
    )

endforeach()


# linking

target_link_libraries(engine
#        ${Box2D}
        "${OPENGL_gl_LIBRARY}"  # We don't need glu for GLEW
        "${GLEW_LIBRARY}"
        "${GLFW}"
        )

target_link_libraries(test_engine
        engine
        )

add_custom_target(run_test
    COMMAND test_engine
    DEPENDS test_engine
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
