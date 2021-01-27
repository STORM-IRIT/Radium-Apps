#ifndef SHADEREDITORWIDGET_H
#define SHADEREDITORWIDGET_H

#include <QWidget>

namespace Ui {
class ShaderEditorWidget;
}

class ShaderEditorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ShaderEditorWidget(QWidget *parent = nullptr);
    ~ShaderEditorWidget();

private:
    Ui::ShaderEditorWidget *ui;
};

#endif // SHADEREDITORWIDGET_H
