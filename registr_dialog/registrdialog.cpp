#include "platform.h"

#include "registrdialog.hpp"

//============================= PUBLIC =============================//

RegistrationDialog::RegistrationDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::RegistrationDialog) {
    ui->setupUi(this);
    connectControls();
}

void RegistrationDialog::setUsernameField(const QString &username) {
    ui->usernameLineEdit->setText(username);
}

//============================= SIGNALS =============================//

void RegistrationDialog::onBackButtonPressed() {
    qDebug("[RegistrationWindow] onBackButtonPressed");
    hide();
    emit hidden();
}

//============================= PRIVATE =============================//

void RegistrationDialog::connectControls() {
    qDebug("[RegistrationWindow] connected: backButton.pressed -> onBackButtonPressed");
    connect(ui->backButton, &QPushButton::pressed, this, &RegistrationDialog::onBackButtonPressed);
}
