#pragma once

#include "platform.h"

enum class DBAdaptorType {
    Authorization,
    Registration,

    Invalid,
};

class DBAdaptor : public QObject {
    Q_OBJECT
public:
    DBAdaptor();
};

class DBAuthAdaptor : public DBAdaptor {
public:
    DBAuthAdaptor();
};

class DBRegAdaptor : public DBAdaptor {
public:
    DBRegAdaptor();
};

std::shared_ptr<DBAdaptor> getAdaptor(DBAdaptorType type);
