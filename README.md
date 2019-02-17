# Simple2DEngine

Simple2DEngine is a simple game engine based on SFML and written in C++.

## Build Status

| Linux GCC | Linux Clang | MacOS | Windows |
|-----------|-------------|-------|---------|
| [![Build Status](https://travis-matrix-badges.herokuapp.com/repos/ilya-bardinov/Simple2DEngine/branches/master/1)](https://travis-ci.org/ilya-bardinov/Simple2DEngine) | [![Build Status](https://travis-matrix-badges.herokuapp.com/repos/ilya-bardinov/Simple2DEngine/branches/master/2)](https://travis-ci.org/ilya-bardinov/Simple2DEngine) | [![Build Status](https://travis-matrix-badges.herokuapp.com/repos/ilya-bardinov/Simple2DEngine/branches/master/3)](https://travis-ci.org/ilya-bardinov/Simple2DEngine) | [![Build Status](https://travis-matrix-badges.herokuapp.com/repos/ilya-bardinov/Simple2DEngine/branches/master/4)](https://travis-ci.org/ilya-bardinov/Simple2DEngine) |

## How to build Simple2DEngine

Debug build which will install itself into default path (`build/dist`)

~~~
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE="Debug"
cmake --build .
cmake --build . --target install
~~~

Release build which will install itself into `install` folder in project root dir
~~~
mkdir build 
cd build
cmake .. -DCMAKE_INSTALL_PREFIX="../install" -DCMAKE_BUILD_TYPE="Release"
cmake --build .
cmake --build . --target install
~~~

Use this commands if you want build and install documentation
~~~
cmake --build . --target doc
cmake --build . --target install
~~~

## Building instructions

### Prerequisites

* `CMake 3.2` or newer
* `SFML 2.5.1` or newer
* Compiler with support for `C++14`
* `git` - for downloading Catch2 for Unit Testing
* `Doxygen` for docs generation (*Graphviz for more graphs in docs, PlantUML for more UML diagrams*, PlantUML needs java)

### Targets

* Build
    * *all*
    * *clean*
    * *install* - install binaries and docs (if builded) into *CMAKE_INSTALL_PREFIX*
    * *Simple2DEngine* - build Simple2DEngine libraries
* Testing
    * *check* - run whole test suite 
    * *checkVerbose* - run whole test suite with verbose
    * *unit* - build and run unit tests only
    * *unitVerbose* - build and run unit tests only with verbose
* Miscellaneous
    * *doc* - build documentation (if doxygen is available)
* External
    * *external-Catch-update* - update Catch (Unit Testing library)

### CMake Variables

* `-DCMAKE_INSTALL_PREFIX` - location for installation
* `-DCMAKE_BUILD_TYPE` - for build type

## License

[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://github.com/ilya-bardinov/Simple2DEngine/blob/master/LICENSE)