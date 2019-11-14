#ifndef QSQLDBMOBILEOPERATORDAO_H
#define QSQLDBMOBILEOPERATORDAO_H

#include "igenericdao.h"
#include <QString>

class MobileOperator;
class SQLConnection;

class QsqldbMobileOperatorDao : public IGenericDao<MobileOperator> {
    private:
        SQLConnection *m_Connection;
        const QString SELECT_ALL_OPERATORS;
        const QString SELECT_OPERATOR_BY_MCC_MNC;
        const QString DELETE_OPERATOR_BY_MCC_MNC;
        const QString UPDATE_OPERATOR_BY_MCC_MNC;
        const QString CREATE_OPERATOR_BY_MCC_MNC_NAME;
        const QString SELECT_COUNT;

        int getRowTotal() noexcept;

    public:
        QsqldbMobileOperatorDao(SQLConnection* connection) noexcept;

        MobileOperator find(const MobileOperator& mobOperator) override;
        QVector<MobileOperator> findAll() override;
        bool create(const MobileOperator& mobOperator) override;
        bool update(const MobileOperator& mobOperator) override;
        bool remove(const MobileOperator& mobOperator) override;
};

#endif // QSQLDBMOBILEOPERATORDAO_H
