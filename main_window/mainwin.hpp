#pragma once

#include <QWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    void setAuthorizedUsername(const QString &uname, const QString &id);

signals:
    void hidden();

private slots:
    void onLogOutButtonClicked();

private:
    std::shared_ptr<Ui::MainWindow> ui;
    QString username;
    QString identificator;

    void connectControls();
};

#include "ui_mainwin.h"
