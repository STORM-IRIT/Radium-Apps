#pragma once

#include <QWidget>

#include <memory>

#include <Core/Utils/Index.hpp>
#include <Gui/ParameterSetEditor/MaterialParameterEditor.hpp>

class QCloseEvent;
class QShowEvent;

namespace Ra {
namespace Engine {
namespace Rendering {
class RadiumEngine;
class RenderObjectManager;
class RenderObject;
} // namespace Rendering
namespace Data {
class Material;
class BlinnPhongMaterial;
} // namespace Data
} // namespace Engine
} // namespace Ra

namespace Ra {
namespace Gui {
class MaterialEditor : public QWidget
{
    Q_OBJECT

  public:
    explicit MaterialEditor( QWidget* parent = nullptr );

    void changeRenderObject( Ra::Core::Utils::Index roIdx );

  signals:
    void materialChanged();

  protected:
    virtual void showEvent( QShowEvent* e ) override;
    virtual void closeEvent( QCloseEvent* e ) override;

  private:
    Ra::Gui::MaterialParameterEditor* m_matParamsEditor;

    bool m_visible;

    Core::Utils::Index m_roIdx;
    std::shared_ptr<Engine::Rendering::RenderObject> m_renderObject;

    std::shared_ptr<Ra::Engine::Data::Material> m_material;
};
} // namespace Gui
} // namespace Ra
