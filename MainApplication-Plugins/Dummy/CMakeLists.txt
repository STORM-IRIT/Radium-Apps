cmake_minimum_required(VERSION 3.6)
#------------------------------------------------------------------------------
# Policies and global parameters for CMake
if (POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif ()
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
# Be nice to visual studio
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#------------------------------------------------------------------------------
# Project definition
project(DummyPlugin VERSION 1.0.0 LANGUAGES CXX)

# Qt stuff
find_package(Radium REQUIRED RadiumCore RadiumEngine RadiumPluginBase)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
set(Qt5_LIBRARIES Qt5::Core Qt5::Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(lplsmt_sources
        src/DummyComponent.cpp
        src/DummyPlugin.cpp
        src/DummySystem.cpp
        src/DummyTask.cpp
        )

set(lplsmt_headers
        src/DummyComponent.hpp
        src/DummyPluginMacros.hpp
        src/DummyPlugin.hpp
        src/DummySystem.hpp
        src/DummyTask.hpp
        )


set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(
        ${CMAKE_CURRENT_BINARY_DIR} # Moc
)

# Our library project uses these sources and headers.
add_library(
        ${PROJECT_NAME} SHARED
        ${lplsmt_sources}
        ${lplsmt_headers}
        ${lplsmt_inlines}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_compile_definitions(${PROJECT_NAME} PRIVATE "-D${PROJECT_NAME}_EXPORTS")

target_link_libraries(${PROJECT_NAME} PUBLIC
        Radium::RadiumCore
        Radium::RadiumEngine
        Radium::RadiumPluginBase
        ${Qt5_LIBRARIES}
        )

configure_radium_plugin_install(
        NAME ${PROJECT_NAME}
)
