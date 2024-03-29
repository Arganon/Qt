#include "sqlconnection.h"
#include <QDebug>
SQLConnection::SQLConnection(QString pathToDb) noexcept : m_Db(QSqlDatabase::addDatabase("QSQLITE"))
{
    m_Db.setDatabaseName(pathToDb);
}

SQLConnection* SQLConnection::getInstance() noexcept {
    static SQLConnection* instance;
    QString pathToDb = QCoreApplication::applicationDirPath() + "/system.db";
    qDebug() << pathToDb;
    if (instance == nullptr) {
        instance = new SQLConnection();
    }

    return instance;
}

bool SQLConnection::connect() noexcept {
    if (!m_Db.open()) {
        return false;
    }
    return true;
}

void SQLConnection::disconnect() noexcept {
    m_Db.close();
}
