#-------------------------------------------------------------------------------
# exampleApp executables setup

project(HelloRadium)

find_package( Radium REQUIRED RadiumCore RadiumEngine RadiumGuiBase RadiumPluginBase)
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

set(APP_NAME "Radium${PROJECT_NAME}")
set(APP_IDEN "com.radium.${PROJECT_NAME}")

if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME ${APP_NAME})
    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_BUNDLE_GUI_IDENTIFIER "${APP_IDEN}")
    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_LONG_VERSION_STRING "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
endif()

install(TARGETS ${PROJECT_NAME} BUNDLE DESTINATION "." RUNTIME DESTINATION bin)

if(APPLE)
    include( BundleUtilities )
    install(CODE "
        include(BundleUtilities)
        fixup_bundle(${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}.app \"\" \"${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}\")
    " COMPONENT Runtime)
endif()

