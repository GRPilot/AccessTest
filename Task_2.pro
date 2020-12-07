QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += \
    auth_window/ \
    main_window/ \
    registr_dialog/ \
    user_info/ \
    database/

SOURCES += \
    auth_window/authwindow.cpp \
    database/dbadaptor.cpp \
    database/dbmgr.cpp \
    main.cpp \
    main_window/mainwin.cpp \
    platform.cpp \
    registr_dialog/registrdialog.cpp \
    user_info/userinfo.cpp

HEADERS += \
    access.hpp \
    auth_window/authwindow.hpp \
    database/dbadaptor.hpp \
    database/dbmgr.hpp \
    errors.hpp \
    main_window/mainwin.hpp \
    platform.h \
    registr_dialog/registrdialog.hpp \
    user_info/userinfo.hpp

FORMS += \
    auth_window/authwindow.ui \
    main_window/mainwin.ui \
    registr_dialog/registrdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
