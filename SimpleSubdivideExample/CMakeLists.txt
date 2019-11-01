cmake_minimum_required(VERSION 3.6)
#-------------------------------------------------------------------------------
# exampleApp executables setup
project(SimpleSubdivide)

find_package( Radium REQUIRED RadiumCore RadiumIO)

#------------------------------------------------------------------------------
# Application specific


add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries (${PROJECT_NAME} PUBLIC Radium::RadiumCore Radium::RadiumIO)

# call the installation configuration (defined in RadiumConfig.cmake)
configure_radium_app_install(
        NAME ${PROJECT_NAME}
)
