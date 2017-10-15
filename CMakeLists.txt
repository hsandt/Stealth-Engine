cmake_minimum_required(VERSION 3.7)
project(StealthEngine VERSION 0.1 LANGUAGES CXX)


# Flags

# C++17
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -Wno-logical-op-parentheses")

# Produce debugging information on debug, optimize on release
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# If clang is used for compilation, force it to emit debug information for libstc++
# https://stackoverflow.com/questions/41745527/cannot-view-stdstring-when-compiled-with-clang
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")

# Output paths

set(CMAKE_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build-${CMAKE_BUILD_TYPE}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")  # executable output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")  # static libraries output directory
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")  # dynamic libraries output directory (unused)

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
        include/application/RunMode.h
        include/application/RunModeData.h
        include/application/WindowManager.h
        include/component/ActorComponent.h
        include/component/Component.h
        include/component/ComponentType.h
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
        include/physics/PhysicsManager.h
        include/physics/Rigidbody.h
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
        src/application/RunModeData.cpp
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
        src/physics/PhysicsManager.cpp
        src/physics/Rigidbody.cpp
        src/renderer/Renderer.cpp
        src/renderer/ShaderUtils.cpp
        src/scene/Scene.cpp
        src/scene/SceneData.cpp
        src/scene/SceneManager.cpp
        src/service/InputManager.cpp
        src/utils/Color.cpp
        )

set(TEST_ENGINE_SOURCE_FILES
        # REFACTOR: move catch and Smoke test framework to yet another SOURCE_FILES
        tests/catch.hpp
        tests/catch_with_main.hpp
        tests/testmain.cpp
        tests/TestFriend.h

        src/test/SmokeTestRunner.cpp
        include/test/SmokeTestRunner.h

        # All actual test cpp files added from here
        tests/factory/TestFactory.cpp
        tests/geometry/TestVec2.cpp
        tests/geometry/TestVec3.cpp
        tests/physics/TestPhysics.cpp
        tests/utils/TestStringUtils.cpp
        )


# Cmake packages

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)


# Rendering libraries: OpenGL, GLEW, GLFW

# FindOpenGL.cmake
find_package(OpenGL 4.5 REQUIRED)  # version requirement does not work, left as a note only
include_directories(${OpenGL_INCLUDE_DIR})

message(STATUS "OpenGL found: ${OPENGL_FOUND}")
message(STATUS "OpenGL xmesa found: ${OPENGL_XMESA_FOUND}")
message(STATUS "OpenGL glu found: ${OPENGL_GLU_FOUND}")
message(STATUS "OpenGL include dir: ${OPENGL_INCLUDE_DIR}")
message(STATUS "OpenGL libraries: ${OPENGL_LIBRARIES}")
message(STATUS "OpenGL gl library: ${OPENGL_gl_LIBRARY}")

# FindGLEW.cmake
find_package(GLEW 2.0 REQUIRED)  # version requirement does not work, left as a note only
include_directories($(GLEW_INCLUDE_DIR))
#add_definitions(-DGLEW_STATIC)  # uncomment to use static library
#add_definitions(-DGLEW_MX)  # uncomment to use thread-safe multiple GL contexts

message(STATUS "GLEW found: ${GLEW_FOUND}")
message(STATUS "GLEW include dir: ${GLEW_INCLUDE_DIR}")
message(STATUS "GLEW libraries: ${GLEW_LIBRARIES}")

# FindGLFW.cmake
find_package(GLFW 3.2 REQUIRED)  # version requirement does not work, left as a note only
include_directories(${GLFW_INCLUDE_DIR})

message(STATUS "GLFW found: ${GLFW_FOUND}")
message(STATUS "GLFW include dir: ${GLFW_INCLUDE_DIR}")
message(STATUS "GLFW libraries: ${GLFW_LIBRARIES}")
#add_definitions(-DGLFW_DLL)  # uncomment if using dynamic library and linking fails


# Physics library: Box2D

find_package(Box2D  REQUIRED)  # version requirement does not work, left as a note only
include_directories(${BOX2D_INCLUDE_DIRS})

message(STATUS "Box2D found: ${BOX2D_FOUND}")
message(STATUS "Box2D include dir: ${BOX2D_INCLUDE_DIR}")
message(STATUS "Box2D libraries: ${BOX2D_LIBRARIES}")


# TODO: use INSTALL to distribute the shared libraries so the app is portable
# this also allows you to copy library headers so that other developers can use the engine

# Targets

# Stealth engine static library
add_library(engine ${ENGINE_SOURCE_FILES})
target_include_directories(engine PUBLIC include)

# Test engine executable
add_executable(test_engine ${TEST_ENGINE_SOURCE_FILES})
target_include_directories(test_engine PRIVATE tests)


# Scan through resource folder for updated files and copy if none existing or changed
# http://qrikko.blogspot.fr/2016/05/cmake-and-how-to-copy-resources-during.html
message(STATUS "Copying resources from ${PROJECT_SOURCE_DIR}...")

file (GLOB_RECURSE resources "${PROJECT_SOURCE_DIR}/resources/*.*")
foreach(resource ${resources})
    get_filename_component(filename ${resource} NAME)
    get_filename_component(dir ${resource} DIRECTORY)
    get_filename_component(dirname ${dir} NAME)
    # DEBUG
#    message(STATUS "(${resource}) filename: ${filename}, dir: ${dir}, dirname: ${dirname}")

    set (output "")

    while(NOT ${dirname} STREQUAL resources)
        get_filename_component(path_component ${dir} NAME)
        set (output "${path_component}/${output}")
        get_filename_component(dir ${dir} DIRECTORY)
        get_filename_component(dirname ${dir} NAME)
        # DEBUG
#        message(STATUS "(${dirname}) output: ${output}, path_component: ${path_component}, dir: ${dir}, dirname: ${dirname}")
    endwhile()

    set(output "${CMAKE_BINARY_DIR}/bin/resources/${output}${filename}")
#    message(STATUS "output: ${output}")

    # Add POST_BUILD command to copy resource file
    # http://stackoverflow.com/questions/13429656/cmake-how-to-copy-contents-of-a-directory-into-build-directory-after-make
    add_custom_command(
        TARGET engine POST_BUILD COMMAND
        ${CMAKE_COMMAND} -E copy_if_different
        ${resource}
        ${output}
        COMMENT "Moving updated resource-file '${filename}'"
    )

endforeach()


# Linking

target_link_libraries(engine
        "${OPENGL_gl_LIBRARY}"  # We don't need _glu_ with GLEW
        "${GLEW_LIBRARIES}"
        "${GLFW_LIBRARIES}"
        "${BOX2D_LIBRARIES}"
        )

target_link_libraries(test_engine
        engine
        )

# Allow to run test_engine executable with "make run_test_engine"
add_custom_target(run_test_engine
        COMMAND test_engine
        DEPENDS test_engine
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        )
