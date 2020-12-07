#pragma once

#include <memory>
#include <functional>

// qt
#include <QtSql>
#include <QDebug>
#include <QObject>
#include <QApplication>
#include <QCryptographicHash>

constexpr char db_fname[] = "users.sqlite";

namespace p {
    QString encode(const QString &text);
}
