#pragma once

enum class FieldStatus {
    SUCCESS = 0,
    ERR_WRONGARGUMENTS,

    ERR_USERNAME_EMPTY,
    ERR_PASSWORD_EMPTY,
    ERR_USERNAME_NOT_FOUND,
};

enum class AppStatus {
    SUCCESS = 0,
    ERR_WRONGARGUMENTS,

    ERR_PERMISSIONS,
    ERR_NOT_FOUND,
};

enum class DBStatus {
    SUCCESS,
    ERR_WRONGARGUMENTS,

    CANNOT_OPEN,
    CANNOT_CREATE,
    CANNOT_UPDATE,

    RECORD_NOTFOUND,
    ERR_ALREADY_EXSISTS,

    SQL_ERRORS,

    ERR_CONNECTION,
    ERR_STATEMENT,
    ERR_TRANSACTION,

    ERR_UNKNOWN,
};

#define SqlErr2DBStat(err) \
    static_cast<DBStatus>((err) + static_cast<int>(DBStatus::SQL_ERRORS))
