#include <Gui/MaterialEditor.hpp>

#include <Engine/Data/Material.hpp>
#include <Engine/RadiumEngine.hpp>
#include <Engine/Rendering/RenderObject.hpp>
#include <Engine/Rendering/RenderObjectManager.hpp>

#include <QCloseEvent>

namespace Ra {
namespace Gui {
MaterialEditor::MaterialEditor( QWidget* parent ) :
    QWidget( parent ), m_visible( false ), m_roIdx( -1 ) {

    auto layout = new QVBoxLayout( this );
    setLayout( layout );
    m_matParamsEditor = new Ra::Gui::MaterialParameterEditor( this );
    connect( m_matParamsEditor,
             &Ra::Gui::MaterialParameterEditor::materialParametersModified,
             [this]() { emit materialChanged(); } );
    layout->addWidget( m_matParamsEditor );
}

void MaterialEditor::changeRenderObject( Core::Utils::Index roIdx ) {
    if ( roIdx.isValid() ) {
        m_renderObject =
            Engine::RadiumEngine::getInstance()->getRenderObjectManager()->getRenderObject( roIdx );

        if ( m_renderObject != nullptr ) {
            m_material = m_renderObject->getMaterial();
            m_roIdx    = roIdx;
            m_matParamsEditor->setupFromMaterial( m_material );
        }
    }
}

void MaterialEditor::showEvent( QShowEvent* e ) {
    QWidget::showEvent( e );
    m_visible = true;
}

void MaterialEditor::closeEvent( QCloseEvent* /*e*/ ) {
    m_visible = false;
    hide();
}

} // namespace Gui
} // namespace Ra
