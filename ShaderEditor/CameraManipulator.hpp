#pragma once

#include <Gui/Viewer/TrackballCameraManipulator.hpp>

class CameraManipulator2D : public Ra::Gui::TrackballCameraManipulator
{
  public:
    /// Default constructor, remove rotate callback
    inline CameraManipulator2D() : Ra::Gui::TrackballCameraManipulator() {
        m_keyMappingCallbackManager.addEventCallback( TRACKBALLCAMERA_ROTATE, []( QEvent* ) {} );
    }
    /// Copy constructor used when switching camera manipulator
    /// Requires that m_target is on the line of sight of the camera.
    /// remove rotate callback
    inline explicit CameraManipulator2D( const CameraManipulator& other ) :
        Ra::Gui::TrackballCameraManipulator( other ) {
        m_keyMappingCallbackManager.addEventCallback( TRACKBALLCAMERA_ROTATE, []( QEvent* ) {} );
    }
};
