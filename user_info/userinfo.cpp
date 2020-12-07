#include "userinfo.hpp"

UserInfo::UserInfo(const QString &uname, const QString &id, Access::access_t uaccess)
    : username(uname), identificator(id), access(uaccess) {
}

QString UserInfo::getUsername() const {
    return username;
}

QString UserInfo::getIdentificator() const {
    return identificator;
}

Access::access_t UserInfo::getAccess() const {
    return access;
}
