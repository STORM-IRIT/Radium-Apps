#include "ShaderEditorWidget.hpp"
#include "ui_ShaderEditorWidget.h"

ShaderEditorWidget::ShaderEditorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShaderEditorWidget)
{
    ui->setupUi(this);
}

ShaderEditorWidget::~ShaderEditorWidget()
{
    delete ui;
}
