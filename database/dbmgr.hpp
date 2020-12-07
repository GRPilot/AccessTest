#pragma once

#include "platform.h"
#include "errors.hpp"
#include "userinfo.hpp"

class DBManager : public QObject {
    Q_OBJECT;

public:
    DBManager();
    enum class ActionType {
        Authorize,
        CreateUser,
        CreateDatabase,
        Invalid,
    };

signals:
    void fail(DBStatus status);
    void logIn(const UserInfo &user_info);
    void created();

public slots:
    void onAuthorizeUser(const QString &username, const QString &pass);
    void onCreateNewUser(const QString &username, const QString &pass);

private:
    struct Action {
        using action_t = std::function<DBStatus(const QVector<QString> &params, UserInfo &userinfo)>;
        action_t execute;
        ActionType type;
    };

    bool isParamsCorrect(const QString &first, const QString &second);
    bool createDatabase();

    Action getActrion(ActionType type);
};

