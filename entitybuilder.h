#ifndef ENTITYBUILDER_H
#define ENTITYBUILDER_H

class Country;
class MobileOperator;
class QSqlQuery;

class EntityBuilder
{
    private:
        EntityBuilder();

    public:
        static Country getCountryObject(QSqlQuery& query);
        static MobileOperator getMobileOperatorObject(QSqlQuery& query);
};

#endif // ENTITYBUILDER_H
