[![codecov](https://codecov.io/gh/hsandt/Stealth-Engine/branch/develop/graph/badge.svg)](https://codecov.io/gh/hsandt/Stealth-Engine)
[![codecov](https://codecov.io/gh/hsandt/Stealth-Engine/branch/master/graph/badge.svg)](https://codecov.io/gh/hsandt/Stealth-Engine)

# Stealth Engine

A 2D game engine written in C++ for development in C++. Supported platforms for both development and build are Linux, OSX, Windows.

This is a personal project I am working on for training purpose. This project started as a framework I intended to use for a top-view Stealth game with a variety of AI applications, but it gradually turned into a generic 2D engine.

# Current features

* Basic physics
* Basic input
* Some OpenGL primitives
* Scene-actor
* Entity-components

## Current work

Integrating CodeCov

## Build dependencies

Here are some build dependencies detailed for Linux Ubuntu, and a bit of OS X.

In doubt, you can also check the .travis.yml file for the most important parts of the setup.

### Box2D

Box2D requires premake5 to be built.
Install premake from [the website](https://premake.github.io/download.html#v5) or use that snippet based on .travis.yml:

    PREMAKE_VERSION="5.0.0-alpha12"
    wget "https://github.com/premake/premake-core/releases/download/v${PREMAKE_VERSION}/premake-${PREMAKE_VERSION}-src.zip"
    rm -rf "premake-${PREMAKE_VERSION}"
    unzip "premake-${PREMAKE_VERSION}-src.zip"
    if [ "$TRAVIS_OS_NAME" == "linux" ]; then
        PREMAKE_BUILD_DIR="gmake.unix"
    elif [ "$TRAVIS_OS_NAME" == "osx" ]; then
        PREMAKE_BUILD_DIR="gmake.macosx"
    fi
   - pushd "premake-${PREMAKE_VERSION}/build/${PREMAKE_BUILD_DIR}"
   - make ${MAKEFLAGS}
   - popd
   - mkdir "/usr/local/bin" -p
   - sudo ln -s "$(pwd)/premake-${PREMAKE_VERSION}/bin/release/premake5" /usr/local/premake5`

### GLFW

To load CMake project, if using X11:

`sudo apt-get install libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev`

To build, if using X11:

`sudo apt-get install libxi-dev`

### OpenGL / GLU

Install the appropriate graphics packages.

MESA:

`sudo apt-get install libglu1-mesa-dev`

This will also install `libgl1-mesa-dev` and `mesa-common-dev` as a dependency. GLU is required for GLEW.

NVIDIA:

Install NVIDIA packages for your graphics card.