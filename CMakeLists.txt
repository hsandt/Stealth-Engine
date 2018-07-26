cmake_minimum_required(VERSION 3.7)

# Policies

cmake_policy(SET CMP0025 NEW)  # AppleClang instead of Clang (may not work, so check both)
cmake_policy(SET CMP0048 NEW)  # Version in project definition


# Project

project(StealthEngine VERSION 0.1 LANGUAGES CXX)


# CMake vars

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: Debug, Release." FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# Cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
include(Export)


# Options

option(BUILD_TESTS "Build tests" OFF)


# Flags

# C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "CMAKE_C_COMPILER_ID: ${CMAKE_C_COMPILER_ID}")
message(STATUS "CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "COMPILER_NAME: ${COMPILER_NAME}")
message(STATUS "CMAKE_CXX_COMPILER_VERSION: ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "CC: ${CC}")
message(STATUS "CXX: ${CXX}")
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    # using Clang
#    set(CXX_VERSION_FLAG "-std=c++17")
#    add_compile_options(-std=c++17) # CMake 2.8.12 or newer
#     add_compile_options("$<$<STREQUAL:$<TARGET_PROPERTY:LINKER_LANGUAGE>,CXX>:-std=c++1z>")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # using GCC
#    set(CXX_VERSION_FLAG "-std=c++1z")
#    add_compile_options(-std=c++17) # CMake 2.8.12 or newer
#    add_compile_options("$<$<STREQUAL:$<TARGET_PROPERTY:LINKER_LANGUAGE>,CXX>:-std=c++17>")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    # using Intel C++
#    set(CXX_VERSION_FLAG "-std=c++17")
#    add_compile_options(-std=c++17) # CMake 2.8.12 or newer
#    add_compile_options("$<$<STREQUAL:$<TARGET_PROPERTY:LINKER_LANGUAGE>,CXX>:-std=c++17>")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # using Visual Studio C++
#    set(CXX_VERSION_FLAG "-std=c++17")
#    add_compile_options(-std=c++17) # CMake 2.8.12 or newer
#    add_compile_options("$<$<STREQUAL:$<TARGET_PROPERTY:LINKER_LANGUAGE>,CXX>:-std=c++17>")
endif()
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_VERSION_FLAG} -Wno-logical-op-parentheses")

#if(ENABLE_COVERAGE)
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
##    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs")
##    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage")
##    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
#endif()

# Produce debugging information on debug, optimize on release
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# If clang is used for compilation, force it to emit debug information for libstc++
# https://stackoverflow.com/questions/41745527/cannot-view-stdstring-when-compiled-with-clang
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")

# Output paths

# preserve original cmake binary dir (current directory in terminal, cmake-build-[config] in CLion)
# to know intermediate source path and find coverage information
set(ORIGINAL_CMAKE_BINARY_DIR "${CMAKE_BINARY_DIR}")
message(STATUS "ORIGINAL_CMAKE_BINARY_DIR: ${ORIGINAL_CMAKE_BINARY_DIR}")

message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
set(CMAKE_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")  # executable output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")  # static libraries output directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")  # dynamic libraries output directory (unused)
set(CMAKE_LIBRARY_PATH "${PROJECT_SOURCE_DIR}/libs")

# Input files

file(GLOB_RECURSE ENGINE_SOURCE_FILES "include/*.h" "src/*.cpp")

# some tests outside the test folder...
file(GLOB_RECURSE TEST_ENGINE_SOURCE_FILES "test/*.h" "test/*.cpp" "include/test/*.h" "src/test/*.cpp")


# Third-party dependencies

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

# GLEW
set(BUILD_UTILS OFF)  # we don't need glewinfo and visualinfo executables
add_subdirectory(third-party/glew-2.1.0/build/cmake)

# GLFW
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
add_subdirectory(third-party/glfw)

# Physics library: Box2D

# Build Box2D with premake with a custom script
# The better way is to prepare an included CMakeLists that does the job locally as the full build command,
# and make sure this step is triggered first via add_subdirectory.
execute_process(COMMAND bash -c
        "cd \"${PROJECT_SOURCE_DIR}/third-party/Box2D\" &&
        premake5 gmake &&
        cd Build &&
        export config=release_x86_64 &&
        make Box2D -j 4")

# Get the library built with premake
find_library(BOX2D_LIBRARY_RELEASE Box2D DIRECTORY ${PROJECT_SOURCE_DIR}/third-party/Box2D/Build/bin/x86_64/Release)
set(BOX2D_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/third-party/Box2D)


# GLEW

# it would be better to use find_package locally and get all the include paths at once...
set(GLEW_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/third-party/glew-2.1.0/include)


# GLFW

set(GLFW_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/third-party/glfw/include)


# Targets

# Stealth engine static library
add_library(engine STATIC "${ENGINE_SOURCE_FILES}")
#set_target_properties(engine PROPERTIES
#        CXX_STANDARD_REQUIRED 17
#        )

target_include_directories(engine
        PUBLIC
        include
        ${BOX2D_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIR}
        ${GLFW_INCLUDE_DIR}
        )

# Scan through resource folder for updated files and copy if none existing or changed
# http://qrikko.blogspot.fr/2016/05/cmake-and-how-to-copy-resources-during.html
message(STATUS "Copying resources from ${PROJECT_SOURCE_DIR}...")
add_copy_command(engine "resources")


# Linking

target_link_libraries(engine
        "${OPENGL_gl_LIBRARY}"  # We don't need _glu_ with GLEW
        "glew_s"
        "glfw"
        "${BOX2D_LIBRARY_RELEASE}"
        )

if(BUILD_TESTS)
    message(STATUS "Adding test configuration...")

    # CMake test support
    enable_testing()
    #    add_subdirectory(test)  # should include directory with CMakeLists containing block below:

    # Test engine executable
    add_executable(test_engine ${TEST_ENGINE_SOURCE_FILES})
    target_include_directories(test_engine PRIVATE test)

    target_link_libraries(test_engine
            engine
            )

    # use the full syntax so CMake can recognize the command as the executable defined above and not a raw path
    add_test(NAME test_engine COMMAND test_engine)

    if(ENABLE_COVERAGE)
        message(STATUS "Adding coverage configuration...")
        target_compile_options(engine PRIVATE --coverage)  # works without, but may be risky
        target_link_libraries(engine --coverage)

        # A custom target triggered with: "make run_test_engine"
        # it will run the engine tests and generate a cover HTML report
        add_custom_command(TARGET test_engine POST_BUILD
                # reset coverage
                COMMAND lcov -z -d ${ORIGINAL_CMAKE_BINARY_DIR}
                # run tests, creating .gcda and .gcno
                COMMAND test_engine
                # generate coverage info without external libs
                COMMAND lcov --capture -d ${ORIGINAL_CMAKE_BINARY_DIR} -o ${CMAKE_BINARY_DIR}/.coverage -q
                COMMAND lcov --remove ${CMAKE_BINARY_DIR}/.coverage '/usr/include/*' '*/third-party/*' -o ${CMAKE_BINARY_DIR}/.coverage -q
                # regenerate HTML report
                COMMAND rm -rf ${CMAKE_BINARY_DIR}/coverage_report
                COMMAND genhtml ${CMAKE_BINARY_DIR}/.coverage -o ${CMAKE_BINARY_DIR}/coverage_report | grep -v "Processing"
                DEPENDS test_engine
                WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
                )
    endif()

endif()
