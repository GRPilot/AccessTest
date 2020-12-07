#pragma once

#include "platform.h"
#include "access.hpp"

class UserInfo {
public:
    explicit UserInfo(const QString &uname = "<unnamed>",
                      const QString  &id = "-1",
                      Access::access_t uaccess = Access::None);

    QString getUsername() const;
    QString  getIdentificator() const;
    Access::access_t getAccess() const;

private:
    QString username;
    QString identificator;
    Access::access_t access;
};

