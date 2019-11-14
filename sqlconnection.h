#ifndef SQLAPI_H
#define SQLAPI_H

#include <QString>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include "requestfactory.h"

class SQLConnection
{
    private:
        QSqlDatabase m_Db;
        explicit SQLConnection(const QString pathToDb = QCoreApplication::applicationDirPath() + "/system.db") noexcept;
        ~SQLConnection();

    public:
        static SQLConnection* getInstance() noexcept;
        bool connect() noexcept;
        void disconnect() noexcept;

        SQLConnection(const SQLConnection &connection) = delete;
        SQLConnection(const SQLConnection &&connection) = delete;
        SQLConnection& operator=(const SQLConnection &rhsConnection) = delete;
        SQLConnection& operator=(SQLConnection &&rhsConnection) = delete;
};

#endif // SQLAPI_H
