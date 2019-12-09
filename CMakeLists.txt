cmake_minimum_required (VERSION 3.6)
project(Radium-apps)
option(RADIUM_APP_FETCH_RADIUM "Fetch, compile and link to a local copy of Radium" OFF)

# set the installation directory for all the apps at once. This will make the same definition ignore on all the
# included applications
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set (CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/installed-${CMAKE_CXX_COMPILER_ID}" CACHE PATH
            "Install path prefix, prepended onto install directories." FORCE )
    message( "Set install prefix to ${CMAKE_INSTALL_PREFIX}" )
    set(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT False)
endif()


add_subdirectory(MainApplication)
add_subdirectory(MainApplication-Plugins) # temporary: plugins need to be moved out of this repository
add_subdirectory(HelloRadium)
add_subdirectory(SimpleSubdivideExample)
