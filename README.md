# Simple2DEngine

![Build Status](https://travis-ci.org/ilya-bardinov/Simple2DEngine.svg?branch=master)
[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://github.com/ilya-bardinov/Simple2DEngine/blob/master/LICENSE)

Simple2DEngine is a simple game engine written in C++.

## How to build Simple2DEngine

Debug build which will install itself into `build/dist`)

~~~
mkdir build
cd build
cmake ..
cmake --build .
cmake --build . --target install
~~~

Release build which will install itself into `/usr` system folder
~~~
mkdir build 
cd build
cmake .. -DCMAKE_INSTALL_PREFIX="/usr" -DCMAKE_BUILD_TYPE="Release"
cmake --build .
sudo cmake --build . --target install
~~~

Use this commands if you want build and install documentation
~~~
cmake --build . --target doc
cmake --build . --target install
~~~

## Building instructions

### Prerequisites

* CMake 3.2 and newer
* Compiler with support for C++14
* git - for downloading Catch2 for Unit Testing
* Doxygen for docs generation (*Graphviz for more graphs in docs, PlantUML for more UML diagrams*, PlantUML needs java)

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
    * *external-Catch-update* - update Catch (Unit test library)

### CMAKE variables

* `-DCMAKE_INSTALL_PREFIX` - location for installation
* `-DCMAKE_BUILD_TYPE` - for build type
