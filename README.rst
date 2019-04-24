Simple2DEngine
==============

Simple2DEngine is a simple game engine based on SFML and written in C++.

Build Status
------------

.. list-table:: 
   :widths: 35 35 35 35
   :header-rows: 1

   * - Linux GCC
     - Linux Clang
     - MacOS
     - Windows
   * - |Linux GCC|
     - |Linux Clang|
     - |MacOS|
     - |Windows|

Documentation
-------------

Documentation status
~~~~~~~~~~~~~~~~~~~~

.. image:: https://readthedocs.org/projects/simple2dengine/badge/?version=master
   :target: https://simple2dengine.readthedocs.io/en/master/?badge=master
   :alt: Documentation Status

You can read online documentation `here 
<https://simple2dengine.readthedocs.io/en/master/>`_.

How to build documentation
~~~~~~~~~~~~~~~~~~~~~~~~~~

First of all you need ``exhale`` python package that can be install by

::

   pip install exhale

In ``CMake`` configuration step set ``BUILD_DOCS`` to ``YES``. Documentation will be build by default and will be in ``docs`` folder.

::

   mkdir build 
   cd build
   cmake -DBUILD_DOCS=YES ..

If you want to install documentation you can use this after doc building.

::

   cmake --build . --target install

Directory for installation can be set by ``-DCMAKE_INSTALL_PREFIX`` variable.

Building instructions
---------------------

Prerequisites
~~~~~~~~~~~~~

-  ``CMake 3.2`` or newer
-  ``SFML 2.5.1`` or newer
-  Compiler with ``C++14`` support 

Targets
~~~~~~~

-  Build

   -  *all*
   -  *clean*
   -  *install* - install binaries and docs (if builded) into *CMAKE_INSTALL_PREFIX*
   -  *simple2dengine* - build Simple2DEngine libraries

-  Testing (if ``BUILD_UNITTESTS`` set to ``YES``)

   -  *unit* - build and run unit tests only
   -  *unitVerbose* - build and run unit tests only with verbose

-  Miscellaneous

   -  *doc* - build documentation

-  External

   -  *external-Catch-update* - update Catch (Unit Testing library)

CMake Variables
~~~~~~~~~~~~~~~

-  ``-DCMAKE_INSTALL_PREFIX`` - location for installation
-  ``-DCMAKE_BUILD_TYPE`` - for build type
-  ``-DBUILD_UNITTESTS`` - boolean for Unit Tests building
-  ``-DBUILD_DOCS`` - boolean for documentation building
-  ``-DBUILD_EXAMPLES`` - boolean for examples building

Build example
~~~~~~~~~~~~~

Debug build which will install itself into default path (``build/dist``).

::

   mkdir build
   cd build
   cmake .. -DCMAKE_BUILD_TYPE="Debug"
   cmake --build .
   cmake --build . --target install

Release build which will install itself into ``install`` directory in project root dir.

::

   mkdir build 
   cd build
   cmake .. -DCMAKE_INSTALL_PREFIX="../install" -DCMAKE_BUILD_TYPE="Release"
   cmake --build .
   cmake --build . --target install

License
-------

|License|

Simple2DEngine uses a BSD 3-clause license.

.. |Linux GCC| image:: https://travis-matrix-badges.herokuapp.com/repos/ilya-bardinov/Simple2DEngine/branches/master/1
   :target: https://travis-ci.org/ilya-bardinov/Simple2DEngine
.. |Linux Clang| image:: https://travis-matrix-badges.herokuapp.com/repos/ilya-bardinov/Simple2DEngine/branches/master/2
   :target: https://travis-ci.org/ilya-bardinov/Simple2DEngine
.. |MacOS| image:: https://travis-matrix-badges.herokuapp.com/repos/ilya-bardinov/Simple2DEngine/branches/master/3
   :target: https://travis-ci.org/ilya-bardinov/Simple2DEngine
.. |Windows| image:: https://travis-matrix-badges.herokuapp.com/repos/ilya-bardinov/Simple2DEngine/branches/master/4
   :target: https://travis-ci.org/ilya-bardinov/Simple2DEngine
.. |License| image:: https://img.shields.io/badge/License-BSD%203--Clause-blue.svg
   :target: https://github.com/ilya-bardinov/Simple2DEngine/blob/master/LICENSE

