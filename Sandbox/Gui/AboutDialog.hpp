#pragma once
#include <Gui/RaGui.hpp>
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class AboutDialog;
}
QT_END_NAMESPACE

namespace Ra {
namespace Gui {

class AboutDialog : public QDialog
{
    Q_OBJECT

  public:
    explicit AboutDialog( QWidget* parent = nullptr );
    ~AboutDialog() override;

  signals:
    /// Emitted when the settings button is pressed
    void settings();

    /// Emitted when the settings help is pressed
    void help();

  private:
    Ui::AboutDialog* ui;
};

} // namespace Gui
} // namespace Ra
