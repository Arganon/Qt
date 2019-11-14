#include "qsqldbmobileoperatordao.h"
#include "mobileoperator.h"
#include "sqlconnection.h"
#include "entitybuilder.h"

QsqldbMobileOperatorDao::QsqldbMobileOperatorDao(SQLConnection* connection) noexcept
    : m_Connection(connection)
    , SELECT_ALL_OPERATORS("SELECT * FROM operators;")
    , SELECT_OPERATOR_BY_MCC_MNC("SELECT * FROM operators WHERE mcc = :mcc AND mnc = :mnc;")
    , DELETE_OPERATOR_BY_MCC_MNC("DELETE FROM operators WHERE mcc = :mcc AND mnc = :mnc;")
    , UPDATE_OPERATOR_BY_MCC_MNC("UPDATE operators SET name = :name WHERE mcc = :mcc AND mnc = :mnc;")
    , CREATE_OPERATOR_BY_MCC_MNC_NAME("INSERT INTO operators (mcc, mnc, name) VALUES (:mcc, :mnc, :name);")
    , SELECT_COUNT("SELECT COUNT(*) FROM countries")
{}

MobileOperator QsqldbMobileOperatorDao::find(const MobileOperator& mobOperator) {
    m_Connection->connect();

    QSqlQuery query;
    query.prepare(SELECT_OPERATOR_BY_MCC_MNC);
    query.bindValue(":mcc", mobOperator.getMcc());
    query.bindValue(":mnc", mobOperator.getMnc());

    query.exec();
    query.first();
    MobileOperator result = EntityBuilder::getMobileOperatorObject(query);

    m_Connection->disconnect();
    return result;
}

QVector<MobileOperator> QsqldbMobileOperatorDao::findAll() {
    QVector<MobileOperator> result;
    result.reserve(getRowTotal() + 42);
    m_Connection->connect();

    QSqlQuery query;
    query.prepare(SELECT_ALL_OPERATORS);

    query.exec();
    query.first();
    result.push_back(EntityBuilder::getMobileOperatorObject(query));

    while (query.next()) {
        result.push_back(EntityBuilder::getMobileOperatorObject(query));
    }

    m_Connection->disconnect();
    return result;
}

bool QsqldbMobileOperatorDao::create(const MobileOperator& mobOperator) {
    m_Connection->connect();
    QSqlQuery query;

    query.prepare(CREATE_OPERATOR_BY_MCC_MNC_NAME);
    query.bindValue(":mcc", mobOperator.getMcc());
    query.bindValue(":mnc", mobOperator.getMnc());
    query.bindValue(":name", mobOperator.getName());

    bool result = query.exec();

    m_Connection->disconnect();

    return result;
}

bool QsqldbMobileOperatorDao::update(const MobileOperator& mobOperator) {
    m_Connection->connect();
    QSqlQuery query;

    query.prepare(UPDATE_OPERATOR_BY_MCC_MNC);
    query.bindValue(":mcc", mobOperator.getMcc());
    query.bindValue(":mnc", mobOperator.getMnc());
    query.bindValue(":name", mobOperator.getName());

    bool result = query.exec();
    m_Connection->disconnect();
    return result;
}

bool QsqldbMobileOperatorDao::remove(const MobileOperator& mobOperator) {
    m_Connection->connect();
    QSqlQuery query;

    query.prepare(DELETE_OPERATOR_BY_MCC_MNC);
    query.bindValue(":mcc", mobOperator.getMcc());
    query.bindValue(":mnc", mobOperator.getMnc());

    bool result = query.exec();
    m_Connection->disconnect();
    return result;
}

int QsqldbMobileOperatorDao::getRowTotal() noexcept {
//    m_Connection->connect();

//    QSqlQuery query(SELECT_COUNT);
//    query.exec();
//    int rowCount = query.value(0).toInt();

//    m_Connection->disconnect();
//    return rowCount;
    return 1000;
}
