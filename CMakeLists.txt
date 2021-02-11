cmake_minimum_required (VERSION 3.6)
project(Radium-apps)

# Set default build type to Release
if(NOT CMAKE_BUILD_TYPE)
  message("No CMAKE_BUILD_TYPE, using default CMAKE_BUILD_TYPE=Release")
  set(CMAKE_BUILD_TYPE "Release")
endif()

# set the installation directory for all the apps at once. This will make the same definition ignore on all the
# included applications
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

    # Compute default paths following Radium's logic
    if (CMAKE_BUILD_TYPE STREQUAL "Release")
        set(RADIUM_APPS_BUNDLE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/installed-${CMAKE_CXX_COMPILER_ID})
    else ()
        set(RADIUM_APPS_BUNDLE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/installed-${CMAKE_CXX_COMPILER_ID}-${CMAKE_BUILD_TYPE})
    endif ()

    set (CMAKE_INSTALL_PREFIX "${RADIUM_APPS_BUNDLE_DIRECTORY}/" CACHE PATH
            "Install path prefix, prepended onto install directories." FORCE )
    message( "Set install prefix to ${CMAKE_INSTALL_PREFIX}" )
    set(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT False)
endif()

# Disable in-source builds
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

# Be nice to visual studio
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Be nice and export compile commands by default, this is handy for clang-tidy
# and for other tools.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Graphical apps
add_subdirectory(Sandbox)
add_subdirectory(ShaderEditor)

# CLI apps
add_subdirectory(CLISubdivider)
add_subdirectory(CLIRenderer)
