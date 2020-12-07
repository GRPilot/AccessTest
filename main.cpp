#include "platform.h"

#include "authwindow.hpp"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    AuthWindow w;
    w.show();
    return a.exec();
}
