#include "daofactory.h"
#include "sqlconnection.h"
#include "qsqldbcountrydao.h"
#include "qsqldbmobileoperatordao.h"

DaoFactory::DaoFactory() noexcept : m_Connection(SQLConnection::getInstance()) {}

DaoFactory* DaoFactory::getInstance() noexcept {
    static DaoFactory* daoFactoryInstance;
    if (daoFactoryInstance == nullptr) {
        daoFactoryInstance = new DaoFactory();
    }

    return daoFactoryInstance;
}

QsqldbCountryDao* DaoFactory::createCountryDao() noexcept {
    return new QsqldbCountryDao(m_Connection);
}

QsqldbMobileOperatorDao* DaoFactory::createMobileOperatorDao() noexcept {
    return new QsqldbMobileOperatorDao(m_Connection);
}
