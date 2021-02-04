#pragma once

#include <QWidget>

namespace Ui {
class ShaderEditorWidget;
}

namespace Ra{
namespace Engine{
namespace Rendering{
    class RenderObject;
    class Renderer;
}
namespace Data {
class ShaderParameterProvider;
}
}
}

///
/// \todo Add automatic UI generation from parameter provider
class ShaderEditorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ShaderEditorWidget(const std::string& v,
                                const std::string& f,
                                std::shared_ptr< Ra::Engine::Rendering::RenderObject > ro,
                                Ra::Engine::Rendering::Renderer * renderer,
                                std::shared_ptr< Ra::Engine::Data::ShaderParameterProvider > paramProvider,
                                QWidget *parent = nullptr);
    ~ShaderEditorWidget();

private slots:
    void updateShadersFromUI();

private:
    Ui::ShaderEditorWidget *ui;
    std::shared_ptr< Ra::Engine::Rendering::RenderObject > _ro;
    Ra::Engine::Rendering::Renderer * _renderer;
    std::shared_ptr< Ra::Engine::Data::ShaderParameterProvider > _paramProvider;
};
