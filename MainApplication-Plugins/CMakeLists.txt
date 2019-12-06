cmake_minimum_required (VERSION 3.6)
project(Radium-MainApplication-Plugins)

# This project is temporary and must be removed ASAP.
# Plugins need to be treated as follow:
#  - If it contains general purpose and validated content: move to https://github.com/STORM-IRIT/Radium-Engine
#  - If is contains demos and tutorials: move to https://github.com/STORM-IRIT/Radium-PluginExample
#  - In other cases, move to https://gitlab.com/Storm-IRIT/radium-official-plugins


option(RADIUM_APP_COMPILE_PLUGINS "Compile plugins (temporary)" OFF)

if( RADIUM_APP_COMPILE_PLUGINS )
    add_subdirectory(Dummy)
endif( RADIUM_APP_COMPILE_PLUGINS )

