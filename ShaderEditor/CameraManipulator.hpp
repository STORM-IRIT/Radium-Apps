#pragma once

#include <Gui/Viewer/TrackballCameraManipulator.hpp>

class CameraManipulator2D : public Ra::Gui::TrackballCameraManipulator
{
  public:
    /// Default constructor
    inline CameraManipulator2D() : Ra::Gui::TrackballCameraManipulator() {}

    /// Copy constructor used when switching camera manipulator
    /// Requires that m_target is on the line of sight of the camera.
    inline explicit CameraManipulator2D( const CameraManipulator& other ) :
        Ra::Gui::TrackballCameraManipulator( other ) {}

    inline bool handleMousePressEvent( QMouseEvent* event,
                                       const Qt::MouseButtons& buttons,
                                       const Qt::KeyboardModifiers& modifiers,
                                       int key ) {
        m_lastMouseX = event->pos().x();
        m_lastMouseY = event->pos().y();

        m_currentAction = Ra::Gui::KeyMappingManager::getInstance()->getAction(
            Ra::Gui::TrackballCameraManipulator::KeyMapping::getContext(),
            buttons,
            modifiers,
            key,
            false );

        // ignore rotate
        if ( m_currentAction == TRACKBALLCAMERA_ROTATE )
        { m_currentAction = Ra::Core::Utils::Index::Invalid(); }
        return true;
    }
};
