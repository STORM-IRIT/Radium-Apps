#pragma once

#include <GuiBase/Viewer/TrackballCameraManipulator.hpp>

class CameraManipulator2D : public Ra::Gui::TrackballCameraManipulator
{
public:
    /// Default constructor
    inline CameraManipulator2D( uint width, uint height )
    : Ra::Gui::TrackballCameraManipulator( width, height ) {}

    /// Copy constructor used when switching camera manipulator
    /// Requires that m_target is on the line of sight of the camera.
    inline explicit CameraManipulator2D( const CameraManipulator& other )
    : Ra::Gui::TrackballCameraManipulator( other ) {}

    inline 
    bool handleMousePressEvent( QMouseEvent* event,
                                const Qt::MouseButtons& buttons,
                                const Qt::KeyboardModifiers& modifiers,
                                int key ) {
    bool handled = false;
    m_lastMouseX = event->pos().x();
    m_lastMouseY = event->pos().y();

    auto action = Ra::Gui::KeyMappingManager::getInstance()->getAction(
        Ra::Gui::KeyMappingManageable<TrackballCameraManipulator>::
        getContext(), buttons, modifiers, key, false );


    if ( action == TRACKBALLCAMERA_PAN )
    {
        m_cameraPanMode = true;
        handled         = true;
    }
    if ( action == TRACKBALLCAMERA_ZOOM )
    {
        m_cameraZoomMode = true;
        handled          = true;
    }

    return handled;
}

};

