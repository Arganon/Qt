#include "qsqldbcountrydao.h"
#include "sqlconnection.h"
#include "country.h"
#include "entitybuilder.h"

QsqldbCountryDao::QsqldbCountryDao(SQLConnection* connection) noexcept
    : m_Connection(connection)
    , SELECT_ALL_COUNTRIES("SELECT * FROM countries;")
    , SELECT_COUNTRY_BY_MCC("SELECT * FROM countries WHERE mcc = :mcc")
    , SELECT_COUNT("SELECT COUNT(*) FROM countries")
{}

Country QsqldbCountryDao::find(const Country& country) {
    m_Connection->connect();

    QSqlQuery query(SELECT_COUNTRY_BY_MCC);
    query.bindValue(":mcc", country.getMcc());
    query.exec();
    query.first();
    Country result = EntityBuilder::getCountryObject(query);

    m_Connection->disconnect();
    return result;
}

QVector<Country> QsqldbCountryDao::findAll() {
    QVector<Country> result;
    result.reserve(getRowTotal() + 42);

    m_Connection->connect();
    QSqlQuery query(SELECT_ALL_COUNTRIES);

    query.exec();
    query.first();
    result.push_back(EntityBuilder::getCountryObject(query));

    while (query.next()) {
        result.push_back(EntityBuilder::getCountryObject(query));
    }
    m_Connection->disconnect();
    return result;
}

bool QsqldbCountryDao::create(const Country&) {
    return false; // We don't want to create any country into DB
}

bool QsqldbCountryDao::update(const Country&) {
    return false; // We don't want to update any country into DB
}

bool QsqldbCountryDao::remove(const Country&) {
    return false; // We don't want to remove any country from DB
}

int QsqldbCountryDao::getRowTotal() noexcept {
    m_Connection->connect();

    QSqlQuery query(SELECT_COUNT);
    query.exec();
    query.first();
    int rowCount = query.value(0).toInt();

    m_Connection->disconnect();
    return rowCount;
}
