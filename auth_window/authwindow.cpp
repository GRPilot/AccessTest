#include "platform.h"

#include "authwindow.hpp"
#include "ui_authwindow.h"

#include "errors.hpp"

//============================= PUBLIC =============================//

AuthWindow::AuthWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::AuthWindow) {
    if(nullptr == ui) {
        throw std::runtime_error("Connot initialize AuthWindow");
    }
    ui->setupUi(this);
    connectControls();
}

//============================= SIGNALS =============================//

void AuthWindow::onLogInButtonPressed() {
    qDebug("onLogInButtonPressed");

    FieldStatus status = checkUser();
    parseFieldStatus(status);

}

void AuthWindow::onRegisterButtonPressed() {
    qDebug("[AuthWindow] onRegisterButtonPressed");

    connectRegisterWnd();
    registerDialog->setUsernameField(ui->usernameLineEdit->text());
    registerDialog->setModal(true);
    this->hide();
    registerDialog->exec();
}

void AuthWindow::onRegistrWindowHiden() {
    qDebug("[AuthWindow] onRegisterButtonPressed");

    disconnectRegisterWnd();

    if(isHidden()) {
        qDebug("[AuthWindow] showing");
        show();
    }
}

void AuthWindow::onMainWindowHiden() {
    qDebug("[AuthWindow] onMainWindowDestroyed");

    ui->usernameLineEdit->clear();
    ui->passwordLineEdit->clear();
    disconnectMainWnd();

    if(isHidden()) {
        show();
    }
}

void AuthWindow::onLogIn(const UserInfo &userinfo) {
    connectMainWnd();
    mainWnd->setAuthorizedUsername(userinfo.getUsername(), userinfo.getIdentificator());
    this->hide();
    mainWnd->show();
}

//============================= PRIVATE =============================//

void AuthWindow::connectControls() {
    qDebug("[AuthWindow] connected: logInButton.pressed -> onBackButtonPressed");
    connect(ui->logInButton, &QPushButton::clicked, this, &AuthWindow::onLogInButtonPressed);
    qDebug("[AuthWindow] connected: pregisterButton.pressed -> onBackButtonPressed");
    connect(ui->registerButton, &QPushButton::clicked, this, &AuthWindow::onRegisterButtonPressed);
}

bool AuthWindow::connectRegisterWnd() {
    qDebug("[AuthWindow] connectRegisterWnd");
    if(nullptr == registerDialog) {
        registerDialog.reset(new RegistrationDialog(nullptr));
    } else {
        qDebug("[AuthWindow] The register window is already created");
    }

    connect(registerDialog.get(), &RegistrationDialog::hidden, this, &AuthWindow::onRegistrWindowHiden);
    return true;
}

bool AuthWindow::disconnectRegisterWnd() {
    qDebug("[AuthWindow] disconnectRegisterWnd");
    if(nullptr == registerDialog) {
        qDebug("[AuthWindow] The register window is already destroyed");
        return true;
    }

    disconnect(registerDialog.get(), &RegistrationDialog::hidden, this, &AuthWindow::onRegistrWindowHiden);
    return true;
}

bool AuthWindow::connectMainWnd() {
    qDebug("[AuthWindow] connectMainWnd");
    if(nullptr == mainWnd) {
        mainWnd.reset(new MainWindow(nullptr));
    } else {
        qDebug("[AuthWindow] The main window is already created");
    }

    connect(mainWnd.get(), &MainWindow::hidden, this, &AuthWindow::onMainWindowHiden);
    return true;
}

bool AuthWindow::disconnectMainWnd() {
    qDebug("[AuthWindow] disconnectMainWnd");
    if(nullptr == mainWnd) {
        qDebug("[AuthWindow] The register window is already destroyed");
        return true;
    }

    disconnect(mainWnd.get(), &MainWindow::hidden, this, &AuthWindow::onMainWindowHiden);

    return mainWnd->close();
}

FieldStatus AuthWindow::checkUser() const {
    const QString &username = ui->usernameLineEdit->text();
    if(username.isEmpty()) {
        return FieldStatus::ERR_USERNAME_EMPTY;
    }
    const QString &password = ui->passwordLineEdit->text();
    if(password.isEmpty()) {
        return FieldStatus::ERR_PASSWORD_EMPTY;
    }

    emit authorizeUser(username, p::encode(password));

    return FieldStatus::SUCCESS;
}

void AuthWindow::parseFieldStatus(const FieldStatus &status) {
    changeIndecatorState(Indecator::Username, FieldStatus::ERR_USERNAME_EMPTY == status);
    changeIndecatorState(Indecator::Password, FieldStatus::ERR_PASSWORD_EMPTY == status);
}

void AuthWindow::changeIndecatorState(AuthWindow::Indecator indecator, bool isWrong) {
    constexpr char format[] = "background-color: %1;";
    constexpr char red[] = " #ec6574";
    constexpr char normal[] = "none";

    switch(indecator) {
        case Indecator::Username:
            ui->usernameIndecator->setStyleSheet(QString{format}.arg(isWrong ? red : normal));
            break;

        case Indecator::Password:
            ui->passwordIndecator->setStyleSheet(QString{format}.arg(isWrong ? red : normal));
            break;
    }
}

