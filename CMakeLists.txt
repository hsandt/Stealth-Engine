cmake_minimum_required(VERSION 3.7)
project(StealthEngine VERSION 0.1 LANGUAGES CXX)

# Third-party dependencies

add_subdirectory(third-party/glew/build/cmake)


# Options

option(BUILD_TESTS "Build tests" OFF)


# Cmake modules

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
include(Export)


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

# tests outside...
file(GLOB_RECURSE ENGINE_SOURCE_FILES "include/*.h" "src/*.cpp")

file(GLOB_RECURSE TEST_ENGINE_SOURCE_FILES2 "test/*.h" "test/*.cpp")

set(TEST_ENGINE_SOURCE_FILES
        # REFACTOR: move catch and Smoke tests framework to yet another SOURCE_FILES
        test/catch.hpp
        test/catch_with_main.hpp
        test/testmain.cpp
        test/TestFriend.h

        src/test/SmokeTestRunner.cpp
        include/test/SmokeTestRunner.h

        # All actual tests cpp files added from here
        test/unittests/factory/TestFactory.cpp
        test/unittests/geometry/TestVec2.cpp
        test/unittests/geometry/TestVec3.cpp
        test/unittests/physics/TestPhysics.cpp
        test/unittests/utils/TestStringUtils.cpp
        )


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


# Targets

# Stealth engine static library
add_library(engine "${ENGINE_SOURCE_FILES}")
target_include_directories(engine PUBLIC include)

# Scan through resource folder for updated files and copy if none existing or changed
# http://qrikko.blogspot.fr/2016/05/cmake-and-how-to-copy-resources-during.html
message(STATUS "Copying resources from ${PROJECT_SOURCE_DIR}...")
add_copy_command(engine "resources")

# Linking

target_link_libraries(engine
        "${OPENGL_gl_LIBRARY}"  # We don't need _glu_ with GLEW
        "${GLEW_LIBRARIES}"
        "${GLFW_LIBRARIES}"
        "${BOX2D_LIBRARIES}"
        )

if(BUILD_TESTS)
    # CMake test support
    enable_testing()
    #    add_subdirectory(test)  # should include directory with CMakeLists containing block below:

    # Test engine executable
    add_executable(test_engine ${TEST_ENGINE_SOURCE_FILES})
    target_include_directories(test_engine PRIVATE test)


    target_link_libraries(test_engine
            engine
            )

    # Allow to run test_engine executable with "make run_test_engine"
    add_custom_target(run_test_engine
            COMMAND test_engine
            DEPENDS test_engine
            WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
            )

    # use the full syntax so CMake can recognize the command as the executable defined above and not a raw path
    add_test(NAME test_engine COMMAND test_engine)

endif()
