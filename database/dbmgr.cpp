#include "platform.h"
#include "access.hpp"
#include "userinfo.hpp"
#include "errors.hpp"

#include "dbmgr.hpp"

DBManager::DBManager() : QObject(nullptr) {
    if(QFile::exists(db_fname)) {
        return;
    }

    if(createDatabase()) {
        qDebug("[DBManager] The database was successfly created");
        return;
    }
    qDebug("[DBManager] Error while creating database");
}

void DBManager::onAuthorizeUser(const QString &username, const QString &pass) {
    if(!isParamsCorrect(username, pass)) {
        emit fail(DBStatus::ERR_WRONGARGUMENTS);
        return;
    }

    QVector params{username, pass};
    DBStatus status;
    UserInfo info;
    {
        Action act = getActrion(ActionType::Authorize);
        status = act.execute(params, info);
    }
    if(DBStatus::SUCCESS == status) {
        emit logIn(info);
        return;
    }

    emit fail(status);
}

void DBManager::onCreateNewUser(const QString &username, const QString &pass) {
    if(!isParamsCorrect(username, pass)) {
        emit fail(DBStatus::ERR_WRONGARGUMENTS);
        return;
    }

    QVector params{username, pass};
    DBStatus status;
    {
        Action act = getActrion(ActionType::CreateUser);
        UserInfo info;
        status = act.execute(params, info);
    }
    if(DBStatus::SUCCESS == status) {
        emit created();
        return;
    }

    emit fail(status);
}

bool DBManager::createDatabase() {
    Action act = getActrion(ActionType::CreateDatabase);
    UserInfo null;
    DBStatus status = act.execute(QVector<QString>{}, null);

    if(DBStatus::SUCCESS != status) {
        emit fail(status);
    }

    return DBStatus::SUCCESS == status;
}

bool DBManager::isParamsCorrect(const QString &first, const QString &second) {
    if(!QFile::exists(db_fname)) {
        qDebug("[DBManager] Error, database file is not exist");
        return false;
    }
    return !(first.isEmpty() || second.isEmpty());
}

DBManager::Action DBManager::getActrion(DBManager::ActionType type) {
    Action::action_t act;
    switch(type) {
        case ActionType::Authorize:
            act = [](const QVector<QString> &params, UserInfo &userinfo) -> DBStatus {
                if(params.size() != 2) {
                    return DBStatus::ERR_WRONGARGUMENTS;
                }

                QSqlDatabase user_db = QSqlDatabase::addDatabase("QSQLITE");
                user_db.setDatabaseName(db_fname);
                if(!user_db.open()) {
                    qDebug() << "[DBManager] Error while opening database: " << user_db.lastError().text();
                    return DBStatus::CANNOT_OPEN;
                }


                QSqlQuery query(QString{"SELECT %1 FROM users WHERE password='%2'"}
                                .arg(params.at(0)).arg(params.at(2)));
                QSqlRecord rec = query.record();

                if(query.next()) {
                    QString uname = query.value(rec.indexOf("username")).toString();
                    QString id = query.value(rec.indexOf("id")).toString();
                    QString access = query.value(rec.indexOf("access")).toString();
                    Access::access_t useraccess = Access::None;
                    if(access.contains("r")) {
                        useraccess |= Access::Read;
                    }
                    if(access.contains("w")) {
                        useraccess |= Access::Write;
                    }

                    userinfo = UserInfo{uname, id, useraccess};
                }
                DBStatus status = DBStatus::SUCCESS;

                if(auto err = query.lastError().type(); QSqlError::ErrorType::NoError != err) {
                    qDebug() << "[DBManager] Error: " << query.lastError().text();
                    status = SqlErr2DBStat(err);
                }
                user_db.close();
                return status;
            };
            break;
        case ActionType::CreateUser:
            act = [](const QVector<QString> &params, UserInfo &) -> DBStatus {
                if(params.size() != 2) {
                    return DBStatus::ERR_WRONGARGUMENTS;
                }

                QSqlDatabase user_db = QSqlDatabase::addDatabase("QSQLITE");
                user_db.setDatabaseName(db_fname);
                if(!user_db.open()) {
                    qDebug() << "[DBManager] Error while opening database: " << user_db.lastError().text();
                    return DBStatus::CANNOT_OPEN;
                }

                QSqlQuery query(QString{"INSERT INTO users(username, password) VALUES(%1, %2)"}
                                .arg(params.at(0)).arg(params.at(1)));

                user_db.close();
                DBStatus status = DBStatus::SUCCESS;
                if(auto err = query.lastError().type(); QSqlError::ErrorType::NoError != err) {
                    qDebug() << "[DBManager] Error: " << query.lastError().text();
                    status = SqlErr2DBStat(err);
                }

                return status;
            };
            break;
        case ActionType::CreateDatabase:
            act = [](const QVector<QString> &, UserInfo &) -> DBStatus {
                if(QFile::exists(db_fname)) {
                    return DBStatus::ERR_ALREADY_EXSISTS;
                }
                QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
                db.setDatabaseName(db_fname);
                if(!db.open()) {
                    qDebug("[DBManager] Error, database file is not exist");
                    return DBStatus::CANNOT_CREATE;
                }
                QSqlQuery query(QString{
                    "CREATE TABLE \"users\" (\n"
                    "    \"id\"	INTEGER NOT NULL,\n"
                    "    \"username\"	TEXT NOT NULL DEFAULT '<unnamed>' UNIQUE,\n"
                    "    \"password\"	TEXT NOT NULL,\n"
                    "    \"access\"	    VARCHAR(3),\n"
                    "    PRIMARY KEY(\"id\" AUTOINCREMENT)\n"
                    ");"
                });
                QSqlError::ErrorType err = query.lastError().type();
                return (QSqlError::ErrorType::NoError == err)
                        ? DBStatus::SUCCESS
                        : SqlErr2DBStat(err);
            };
            break;
        default: return Action{ nullptr, ActionType::Invalid };
    }
    return Action{
        act, type
    };
}
