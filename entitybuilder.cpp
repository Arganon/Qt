#include "entitybuilder.h"
#include "country.h"
#include "mobileoperator.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

EntityBuilder::EntityBuilder() {}

Country EntityBuilder::getCountryObject(QSqlQuery &query) {
    int mcc = query.value("mcc").toInt();
    QString countryName = query.value("name").toString();
    QString countryCode = query.value("code").toString();

    return Country(mcc, countryName, countryCode);
}

MobileOperator EntityBuilder::getMobileOperatorObject(QSqlQuery& query) {
    int mcc = query.value("mcc").toInt();
    int mnc = query.value("mnc").toInt();
    QString operatorName = query.value("name").toString();

    return MobileOperator(mcc, mnc, operatorName);
}
