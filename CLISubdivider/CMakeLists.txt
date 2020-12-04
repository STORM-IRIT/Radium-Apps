cmake_minimum_required(VERSION 3.6)
#-------------------------------------------------------------------------------
# exampleApp executables setup
project(Radium-CLI-Subdivider)

find_package( Radium REQUIRED Core IO)

#------------------------------------------------------------------------------
# Application specific


add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries (${PROJECT_NAME} PUBLIC Radium::Core Radium::IO)

# call the installation configuration (defined in RadiumConfig.cmake)
configure_radium_app(
    NAME ${PROJECT_NAME}
)
