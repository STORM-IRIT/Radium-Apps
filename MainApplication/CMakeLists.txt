# Build MainApplication
cmake_minimum_required(VERSION 3.8)
if(${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} VERSION_GREATER "3.9")
    cmake_policy(SET CMP0071 NEW)
endif()

#-------------------------------------------------------------------------------
# exampleApp executables setup
project(main-app)

find_package( Radium REQUIRED RadiumCore RadiumEngine RadiumGuiBase RadiumPluginBase RadiumIO)

#------------------------------------------------------------------------------
# Application specific


find_package(Qt5 COMPONENTS Core Widgets OpenGL REQUIRED)
set( Qt5_LIBRARIES Qt5::Core Qt5::Widgets Qt5::OpenGL )

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(app_sources
        main.cpp
        MainApplication.cpp
        Gui/ColorWidget.cpp
        Gui/MainWindow.cpp
        Gui/MaterialEditor.cpp
        Gui/TransformEditorWidget.cpp
    )

set(app_headers
        MainApplication.hpp
        Gui/ColorWidget.hpp
        Gui/MainWindow.hpp
        Gui/MaterialEditor.hpp
        Gui/RotationEditor.hpp
        Gui/TransformEditorWidget.hpp
        Gui/VectorEditor.hpp
   )

set(app_uis
        Gui/ui/MainWindow.ui
        Gui/ui/MaterialEditor.ui
        Gui/ui/RotationEditor.ui
        Gui/ui/VectorEditor.ui
   )

qt5_wrap_ui(app_uis_moc ${app_uis})

set(app_resources
        Resources/ApplicationIcons.qrc
   )


set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR} # Moc
    )

add_executable(
    ${PROJECT_NAME} MACOSX_BUNDLE
    ${app_sources}
    ${app_headers}
    ${app_inlines}
    ${app_uis_moc}
    ${resources}
    )

target_link_libraries (${PROJECT_NAME} PUBLIC
    Radium::RadiumCore
    Radium::RadiumEngine
    Radium::RadiumGuiBase
    Radium::RadiumIO
    ${Qt5_LIBRARIES})

configure_radium_app_install(
        NAME ${PROJECT_NAME}
)

# radium_cotire( ${app_target} )
