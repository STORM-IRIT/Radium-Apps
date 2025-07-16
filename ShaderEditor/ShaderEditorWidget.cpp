#include "ShaderEditorWidget.hpp"
#include "ui_ShaderEditorWidget.h"

#include "MyParameterProvider.hpp"

#include <Engine/Rendering/RenderObject.hpp>
#include <Engine/Rendering/RenderObjectManager.hpp>
#include <Engine/Rendering/Renderer.hpp>

// include the custom material definition
#include <Engine/Data/RawShaderMaterial.hpp>

#include <QPushButton>
#include <QString>
#include <QTextEdit>

ShaderEditorWidget::ShaderEditorWidget(
    const std::string& v,
    const std::string& f,
    std::shared_ptr<Ra::Engine::Rendering::RenderObject> ro,
    Ra::Engine::Rendering::Renderer* renderer,
    std::shared_ptr<Ra::Engine::Data::ShaderParameterProvider> paramProvider,
    QWidget* parent ) :
    QWidget( parent ),
    ui( new Ui::ShaderEditorWidget ),
    _ro( ro ),
    _renderer( renderer ),
    _paramProvider( paramProvider ) {
    ui->setupUi( this );

    ui->_vertShaderEdit->setPlainText( QString::fromStdString( v ) );
    ui->_fragShaderEdit->setPlainText( QString::fromStdString( f ) );

    connect( ui->_compileShaders,
             &QPushButton::clicked,
             this,
             &ShaderEditorWidget::updateShadersFromUI );
}

ShaderEditorWidget::~ShaderEditorWidget() {
    delete ui;
}

void ShaderEditorWidget::updateShadersFromUI() {
    using ShaderConfigType = std::vector<std::pair<Ra::Engine::Data::ShaderType, std::string>>;

    const ShaderConfigType config { { Ra::Engine::Data::ShaderType::ShaderType_VERTEX,
                                      ui->_vertShaderEdit->toPlainText().toStdString() },
                                    { Ra::Engine::Data::ShaderType::ShaderType_FRAGMENT,
                                      ui->_fragShaderEdit->toPlainText().toStdString() } };

    auto mat = static_cast<Ra::Engine::Data::RawShaderMaterial*>( _ro->getMaterial().get() );
    mat->updateShaders( config, _paramProvider );
    _renderer->buildRenderTechnique( _ro.get() );
}
