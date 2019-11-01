# Radium Applications
These are applications based on the [Radium engine](https://github.com/STORM-IRIT/Radium-Engine)

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

# find and configura the Radium environment for the application
# Note that only the required component of Radium might be fetched.
find_package( Radium REQUIRED RadiumCore RadiumEngine RadiumGuiBase RadiumPluginBase RadiumIO)

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
    Radium::RadiumCore
    Radium::RadiumEngine
    Radium::RadiumGuiBase
    MySuperLibrary
    ... )

# call the installation configuration (defined in RadiumConfig.cmake)
configure_radium_app_install(
        NAME ${PROJECT_NAME}
        [RESOURCES list of resources directory]
)
```

## Configure the application
A Radium application could not be compiled in its source tree.
You then must first create a buid directory that will be the root of the buildtree.
 
    mkdir build
    cd build
    
If the Radium environment was installed in the directory `pathToRadiumInstallation`, 
configure the project with :
    
    cmake -DCMAKE_PREFIX_PATH=pathToRadiumInstallation


By default, the application will be installed in a directory 
called `installed-<Compiler_id>` in your buildtree. This installed
application is then fully relocatable and distribuable.
