#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class AuthWindow;
}
QT_END_NAMESPACE

#include "registrdialog.hpp"
#include "mainwin.hpp"
#include "userinfo.hpp"

enum class FieldStatus;

class AuthWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit AuthWindow(QWidget *parent = nullptr);

signals:
    void authorizeUser(const QString &username, const QString &pass) const;

private slots:
    void onLogInButtonPressed();
    void onRegisterButtonPressed();

    void onRegistrWindowHiden();
    void onMainWindowHiden();

    void onLogIn(const UserInfo &user_info);

private:
    std::shared_ptr<Ui::AuthWindow> ui;
    std::unique_ptr<RegistrationDialog> registerDialog;
    std::unique_ptr<MainWindow> mainWnd;

    void connectControls();

    bool connectRegisterWnd();
    bool disconnectRegisterWnd();

    bool connectMainWnd();
    bool disconnectMainWnd();

    FieldStatus checkUser() const;
    void parseFieldStatus(const FieldStatus &status);

    enum class Indecator {
        Username,
        Password
    };

    void changeIndecatorState(Indecator indecator, bool isWrong);
};

#include "ui_authwindow.h"
