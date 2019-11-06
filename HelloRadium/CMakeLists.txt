cmake_minimum_required(VERSION 3.6)
#-------------------------------------------------------------------------------
# exampleApp executables setup
project(HelloRadium)
# Set default install location to installed-<Compiler_ID> folder in build dir
# we do not want to install to /usr by default
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set (CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/installed-${CMAKE_CXX_COMPILER_ID}" CACHE PATH
            "Install path prefix, prepended onto install directories." FORCE )
    message( "Set install prefix to ${CMAKE_INSTALL_PREFIX}" )
endif()

find_package( Radium REQUIRED RadiumCore RadiumEngine RadiumGuiBase RadiumPluginBase RadiumIO)

#------------------------------------------------------------------------------
# Application specific

find_package(Qt5 COMPONENTS Core Widgets OpenGL REQUIRED)
set( Qt5_LIBRARIES Qt5::Core Qt5::Widgets Qt5::OpenGL )

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(${PROJECT_NAME} MACOSX_BUNDLE
    minimalradium.hpp
    minimalradium.cpp
    minimalapp.hpp
    minimalapp.cpp
    main.cpp)

target_link_libraries (${PROJECT_NAME} PUBLIC
    Radium::RadiumCore
    Radium::RadiumEngine
    Radium::RadiumGuiBase
    ${Qt5_LIBRARIES})
target_include_directories( ${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} )

# call the installation configuration (defined in RadiumConfig.cmake)
configure_radium_app_install(
        NAME ${PROJECT_NAME}
)
