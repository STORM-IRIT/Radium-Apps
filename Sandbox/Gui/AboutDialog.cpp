#include "ui_AboutDialog.h"
#include <Gui/AboutDialog.hpp>
#include <QPushButton>

namespace Ra {
namespace Gui {
AboutDialog::AboutDialog( QWidget* parent ) : QDialog( parent ), ui( new Ui::AboutDialog ) {
    ui->setupUi( this );
    ui->aboutbuttons->button( QDialogButtonBox::RestoreDefaults )->setText( "Settings" );
    connect( ui->aboutbuttons->button( QDialogButtonBox::RestoreDefaults ),
             &QPushButton::pressed,
             this,
             &AboutDialog::settings );
}

AboutDialog::~AboutDialog() {
    delete ui;
}

} // namespace Gui
} // namespace Ra
