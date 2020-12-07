#pragma once

#include <QDialog>

namespace Ui {
class RegistrationDialog;
}

class RegistrationDialog : public QDialog {
    Q_OBJECT

public:
    explicit RegistrationDialog(QWidget *parent = nullptr);

    void setUsernameField(const QString &username);

signals:
    void hidden();

private slots:
    void onBackButtonPressed();

private:
    std::shared_ptr<Ui::RegistrationDialog> ui;

    void connectControls();
};

#include "ui_registrdialog.h"
