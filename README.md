# Radium Applications
Radium is a research 3D Engine for rendering, animation and processing.
It is developed and maintained by the [STORM research group](https://www.irit.fr/STORM/site/).

This repository holds front-end applications (GUI, command line) based on Radium Libraries
 - Sandbox: Graphical frontend of the Radium Engine. This application aims at demonstrating the capabilities of the Radium Libraries. It can be extended using Radium plugins.
 - CLISubdivider: Example of command line application. Loads obj files and run subdivision algorithms implemented with OpenMesh.
 
To get more details about each application, checkout the Readme files in each application directory.

# How to get these applications
## Pre-compiled binaries
Pre-compiled binaries can be downloaded from https://github.com/STORM-IRIT/Radium-Releases/releases/.

The downloaded archive contains:
 - Radium libraries
 - Radium example applications (this repository)

## Compilation instructions
To compile this repository, you first need to compile and install the [Radium libraries](https://github.com/STORM-IRIT/Radium-Engine).
Then, configure this project using cmake. 
You need to tell cmake where to find the installed Radium package by setting the `Radium_DIR` variable to the right location (see more details in Radium Engine documentation: https://storm-irit.github.io/Radium-Engine/).


# How to write your own application
This repository also demonstrate how to write applications and extend Radium ecosystem.
Radium provides a set of tools simplifying the deployment of such applications,
which among other things take care of the portability and relocatability of the
binaries.

Other minimal application examples are available at https://github.com/STORM-IRIT/Radium-Engine/tree/master/tests/ExampleApps.

In order to write your own application, you need to follow theses instructions.


## Setting a CMakeLists.txt to compile and install an application
To compile and execute an application, either in the build tree
or after installation, the Radium environment must be configured,
compiled and installed beforehand.

The main CMakeLists.txt file for compiling a Radium Based application
could be as simple as
```cmake
# set the minimal cmake version supported by Radium cmake system
cmake_minimum_required(VERSION 3.6)
# set the name of the project (and then the name of the executable)
project(HelloRadium)

# find and configure the Radium environment for the application
# Note that only the required component of Radium might be fetched.
find_package( Radium REQUIRED Core Engine GuiBase PluginBase IO)

#------------------------------------------------------------------------------
# Application specific configuration

# find and configure all packages and functionalities needed
# by the application
find_package( ... )

# set up the application. For portability reasons, do not forget the MACOSX_BUNDLE
# on MacOsX, if MACOSX_BUNDLE is not set, generate a command line tool
# if MACOSX_BUNDLE is set, generate a relocatable bundle
add_executable(${PROJECT_NAME} [MACOSX_BUNDLE]
    # give here the list of source files associated with the applciation
    # this list must contain all the files (.cpp, .hpp, .ui, ...) of the application

)

#link with the libraries needed by the application
target_link_libraries (${PROJECT_NAME} PUBLIC
    Radium::Core
    Radium::Engine
    Radium::GuiBase
    MySuperLibrary
    ... )

# call the installation configuration (defined in RadiumConfig.cmake)
configure_radium_app(
        NAME ${PROJECT_NAME}
        [USE_PLUGINS]   # enable plugin support
        [RESOURCES list of resources directory]
)
```

### Configure the application
Radium does not support in-source builds (it is bad practice anyway).
You then must first create a buid directory that will be the root of the buildtree.

    mkdir build
    cd build

If the Radium environment was installed in the directory `pathToRadiumInstallation`,
configure the project with :

    cmake ../ -DRadium_DIR=pathToRadiumInstallation/lib/cmake/Radium


By default, the application will be installed in a directory
called `installed-<Compiler_id>` in the application buildtree. This installed
application is then fully relocatable and distribuable.
You can change this default behavior by setting `CMAKE_INSTALL_PREFIX`. To generate
the application in `pathToRadiumInstallation/bin/`, set `-DCMAKE_INSTALL_PREFIX=pathToRadiumInstallation`
