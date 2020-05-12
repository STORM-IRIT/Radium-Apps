#ifndef RADIUMENGINE_MAINWINDOW_HPP
#define RADIUMENGINE_MAINWINDOW_HPP

#include <GuiBase/MainWindowInterface.hpp>
#include <GuiBase/RaGuiBase.hpp>
#include <GuiBase/SelectionManager/SelectionManager.hpp>
#include <GuiBase/TimerData/FrameTimerData.hpp>
#include <GuiBase/TreeModel/EntityTreeModel.hpp>
#include <Gui/MaterialEditor.hpp>

#include "ui_MainWindow.h"
#include <QMainWindow>

#include <QEvent>
#include <qdebug.h>

namespace Ra {
namespace Engine {
class Entity;
class SkeletonComponent;
class SkinningComponent;
}
} // namespace Ra

namespace Ra {
namespace Gui {
class EntityTreeModel;
class Viewer;
} // namespace Gui
} // namespace Ra

namespace Ra {
namespace Plugins {
class RadiumPluginInterface;
}
} // namespace Ra

namespace Ra {
namespace Gui {

/// This class manages most of the GUI of the application :
/// top menu, side toolbar and side dock.
class MainWindow : public Ra::GuiBase::MainWindowInterface, private Ui::MainWindow
{
    Q_OBJECT

  public:
    /// Constructor and destructor.
    explicit MainWindow( QWidget* parent = nullptr );
    virtual ~MainWindow();

    /// Access the viewer, i.e. the rendering widget.
    Viewer* getViewer() override;

    /// Access the selection manager.
    GuiBase::SelectionManager* getSelectionManager() override;

    /// Update the ui from the plugins loaded.
    void updateUi( Plugins::RadiumPluginInterface* plugin ) override;

    /// Update the UI ( most importantly gizmos ) to the modifications of the engine/
    void onFrameComplete() override;

    /// Add a renderer in the application: UI, viewer.
    void addRenderer( const std::string& name, std::shared_ptr<Engine::Renderer> e ) override;

  public slots:
    /// Callback to rebuild the item model when the engine objects change.
    void onItemAdded( const Engine::ItemEntry& ent );

    void onItemRemoved( const Engine::ItemEntry& ent );

    // Frame timers ui slots
    void onUpdateFramestats( const std::vector<FrameTimerData>& stats );

    // Selection tools
    void onSelectionChanged( const QItemSelection& selected, const QItemSelection& deselected );

    // Gizmo buttons slots
    void gizmoShowNone();
    void gizmoShowTranslate();
    void gizmoShowRotate();
    void gizmoShowScale();

    // Keymapping configuration tool
    void reloadConfiguration();
    void loadConfiguration();

    /// Slot for the tree view checkboxes
    void setROVisible( Core::Utils::Index roIndex, bool visible );

    /// Reset the camera to see all visible objects
    void fitCamera();
    /// clear selection, fit camera and update material name in ui
    void postLoadFile( const std::string& filename ) override;

    /// Slot for the "edit" button.
    void editRO();

    /// Cleanup resources.
    void cleanup() override;

    /// Show or hide all render objects
    void showHideAllRO();

  signals:
    /// Emitted when the frame loads
    void fileLoading( const QString path );

    /// Emitted when the user changes the timer box ("Frame average over count")
    void framescountForStatsChanged( int count );

    /// Emitted when a new item is selected. An invalid entry is sent when no item is selected.
    void selectedItem( const Engine::ItemEntry& entry );

  private slots:
    /// \name Time events
    /// \{

    /// Slot for the user requesting to play/pause time through the time actions.
    void on_actionPlay_triggered( bool checked );

    /// Slot for the user requesting to step time.
    void on_actionStep_triggered();

    /// Slot for the user requesting to reset time.
    void on_actionStop_triggered();
    /// \}

    /// \name Skeleton-based Animation
    /// \{

    /// Slot for the user requesting x-ray animation skeletons (through the toolbar).
    void on_actionXray_triggered( bool checked );

    /// Slot for the user requesting to use LBS skinning.
    void on_actionLBS_triggered();

    /// Slot for the user requesting to use DQS skinning.
    void on_actionDQS_triggered();

    /// Slot for the user requesting to use CoR skinning.
    void on_actionCoR_triggered();

    /// Slot for the user requesting to use STBS-LBS skinning.
    void on_actionSTBSLBS_triggered();

    /// Slot for the user requesting to use STBS-DQS skinning.
    void on_actionSTBSDQS_triggered();

    /// Slot for the user changing the skeleton animation timestep.
    void on_m_timeStep_currentIndexChanged( int index );

    /// Slot for the user changing the animation speed.
    void on_m_speed_valueChanged( double arg1 );

    /// Slot for the user toggling the animation ping-pong mode.
    void on_m_pingPong_toggled( bool checked );

    /// Slot for the user toggling the animation auto-repeat mode.
    void on_m_autoRepeat_toggled( bool checked );

    /// Slot for the user changing the skeleton animation.
    void on_m_currentAnimation_currentIndexChanged( int index );

    /// Slot for the user adding a new skeleton animation.
    void on_m_newAnim_clicked();

    /// Slot for the user removing a skeleton animation.
    void on_m_removeAnim_clicked();

    /// Slot for the user wanting to load a skeleton animation from a file.
    void on_m_loadAnim_clicked();

    /// Slot for the user wanting to save the current skeleton animation to a file.
    void on_m_saveAnim_clicked();

    /// Slot for the user requesting x-ray animation skeletons (through the toolbox).
    void on_m_xray_clicked( bool checked );

    /// Slot for the user requesting to show the skeleton.
    void on_m_showSkeleton_toggled( bool checked );

    /// Slot for the user changing the skinning method.
    void on_m_skinningMethod_currentIndexChanged( int index );

    /// Slot for the user requesting to display per-bone skinning weights.
    void on_m_showWeights_toggled( bool checked );

    /// Slot for the user selecting the kind of displayed skinning weights.
    void on_m_weightsType_currentIndexChanged( int index );
    /// \}

  private:
    /// Connect qt signals and slots. Called once by the constructor.
    void createConnections();

    // Updates the Tracking info according to the selected feature, if any.
    void updateTrackedFeatureInfo();

    virtual void closeEvent( QCloseEvent* event ) override;

    /// Update displayed texture according to the current renderer
    void updateDisplayedTexture();

    /// Set the background color (updates viewer). If c is invalid, the color is fetch from
    /// QSettings.
    void updateBackgroundColor( QColor c = QColor() );

  private slots:
    /// Slot for the "load file" menu.
    void loadFile();

    /// Slot for the "material editor"
    void openMaterialEditor();

    /// Slot for the user changing the current shader
    void changeRenderObjectShader( const QString& shaderName );

    /// Slot for the user changing the current renderer
    void onCurrentRenderChangedInUI();

    /// Slot for the picking results from the viewer.
    void handlePicking( const Ra::Engine::Renderer::PickingResult& pickingResult );

    // Slot to init renderers once gl is ready
    void onGLInitialized();

    /// Slot to accept a new renderer
    void onRendererReady();

    /// Exports the mesh of the currently selected object to a file.
    void exportCurrentMesh();

    /// Remove the currently selected item (entity, component or ro)
    void deleteCurrentItem();

    /// Clears all entities and resets the camera.
    void resetScene();

    /// Allow to pick using a circle
    void toggleCirclePicking( bool on );

    /// set the current background color
    void on_m_currentColorButton_clicked();

    /// activate trackball camera manipulator
    void activateTrackballManipulator();

    /// activate flight-mode camera manipulator
    void activateFlightManipulator();

    /// Allow to manage registered plugin paths
    /// @todo : for now, only add a new path ... make full management available
    void addPluginPath();
    /// Remove all registered plugin directories
    void clearPluginPaths();

  private:
    /// Stores the internal model of engine objects for selection and visibility.
    GuiBase::ItemModel* m_itemModel{nullptr};

    /// Stores and manages the current selection.
    GuiBase::SelectionManager* m_selectionManager{nullptr};

    /// Widget to allow material edition.
    std::unique_ptr<MaterialEditor> m_materialEditor{nullptr};

    /// viewer widget
    Ra::Gui::Viewer* m_viewer{nullptr};

    /// Selected SkeletonComponent.
    Ra::Engine::SkeletonComponent* m_currentSkeleton{nullptr};

    /// Selected SkinningComponent.
    Ra::Engine::SkinningComponent* m_currentSkinning{nullptr};
};

} // namespace Gui
} // namespace Ra

#endif // RADIUMENGINE_MAINWINDOW_HPP
