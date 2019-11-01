cmake_minimum_required (VERSION 3.6)
project(Radium-apps)
option(RADIUM_APP_FETCH_RADIUM "Fetch, compile and link to a local copy of Radium" OFF)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set (CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/installed-${CMAKE_CXX_COMPILER_ID}" CACHE PATH
            "Install path prefix, prepended onto install directories." FORCE )
    set (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT FALSE)
    message( "Set install prefix to ${CMAKE_INSTALL_PREFIX}" )
endif()


add_subdirectory(MainApplication)
add_subdirectory(HelloRadium)
add_subdirectory(SimpleSubdivideExample)
