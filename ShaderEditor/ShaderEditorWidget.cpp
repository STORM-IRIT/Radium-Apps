#include "ShaderEditorWidget.hpp"
#include "ui_ShaderEditorWidget.h"

#include "MyParameterProvider.hpp"

#include <Engine/Renderer/Renderer.hpp>
#include <Engine/Renderer/RenderObject/RenderObjectManager.hpp>
#include <Engine/Renderer/RenderObject/RenderObject.hpp>

// include the custom material definition
#include <Engine/Renderer/Material/RawShaderMaterial.hpp>

#include <QPushButton>
#include <QString>
#include <QTextEdit>

ShaderEditorWidget::ShaderEditorWidget(
                                const std::string& v,
                                const std::string& f,
                                std::shared_ptr< Ra::Engine::RenderObject > ro,
                                Ra::Engine::Renderer * renderer,
                                std::shared_ptr< Ra::Engine::ShaderParameterProvider > paramProvider,
                                QWidget *parent) :
    QWidget( parent ),
    ui( new Ui::ShaderEditorWidget ),
    _ro( ro ),
    _renderer( renderer ),
    _paramProvider( paramProvider )
{
    ui->setupUi(this);

    ui->_vertShaderEdit->setPlainText( QString::fromStdString( v ) );
    ui->_fragShaderEdit->setPlainText( QString::fromStdString( f ) );

    connect( ui->_compileShaders, &QPushButton::clicked, this, &ShaderEditorWidget::updateShadersFromUI );
}

ShaderEditorWidget::~ShaderEditorWidget()
{
    delete ui;
}

void
ShaderEditorWidget::updateShadersFromUI() 
{
    using ShaderConfigType = std::vector<std::pair<Ra::Engine::ShaderType, std::string>> ;

    const ShaderConfigType config {
        {Ra::Engine::ShaderType::ShaderType_VERTEX,   ui->_vertShaderEdit->toPlainText().toStdString()},
        {Ra::Engine::ShaderType::ShaderType_FRAGMENT, ui->_fragShaderEdit->toPlainText().toStdString()}};

    auto mat           = static_cast<Ra::Engine::RawShaderMaterial*>( _ro->getMaterial().get() );
    mat->updateShaders( config, _paramProvider );
    _renderer->buildRenderTechnique( _ro.get() );
}
