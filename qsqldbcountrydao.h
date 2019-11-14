#ifndef QSQLDBCOUNTRYDAO_H
#define QSQLDBCOUNTRYDAO_H

#include <QString>
#include "igenericdao.h"

class Country;
class SQLConnection;

class QsqldbCountryDao : public IGenericDao<Country> {
    private:
        SQLConnection* m_Connection;
        const QString SELECT_ALL_COUNTRIES;
        const QString SELECT_COUNTRY_BY_MCC;
        const QString SELECT_COUNT;

        int getRowTotal() noexcept;

    public:
        explicit QsqldbCountryDao(SQLConnection* connection) noexcept;

        Country find(const Country& country) override;
        QVector<Country> findAll() override;
        bool create(const Country&) override;
        bool update(const Country&) override;
        bool remove(const Country&) override;
};

#endif // QSQLDBCOUNTRYDAO_H
