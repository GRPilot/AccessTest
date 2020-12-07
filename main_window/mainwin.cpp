#include "platform.h"

#include "mainwin.hpp"

//============================= PUBLIC =============================//

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connectControls();
}

void MainWindow::setAuthorizedUsername(const QString &uname, const QString &id) {
    setWindowTitle(uname + " | " + windowTitle());
    ui->usernamelabel->setText(uname);
    ui->idLabel->setText(id);
    username = uname;
    identificator = id;
}

//============================= SIGNALS =============================//

void MainWindow::onLogOutButtonClicked() {
    hide();
    emit hidden();
}

//============================= PRIVATE =============================//

void MainWindow::connectControls() {
    connect(ui->logOutButton, &QPushButton::clicked, this, &MainWindow::onLogOutButtonClicked);
}
