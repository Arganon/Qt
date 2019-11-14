#ifndef COUNTRY_H
#define COUNTRY_H

#include <QString>
#include <QVector>
#include "ibasedescribeobj.h"
#include "mobileoperator.h"

class Country
{
    private:
        int m_Mcc;
        QString m_CountryName;
        QString m_CountryCode;
        QVector<MobileOperator> m_MobileOperators;

    public:
        Country() = default;
        Country(const int &mcc, const QString &countryName, const QString &countryCode) noexcept;

        Country(const Country &rhs);

        int getMcc() const noexcept;
        QString getName() const noexcept;
        QString getCode() const noexcept;
        QVector<MobileOperator> getMobileOperators() const noexcept;
        bool addMobileOperator(MobileOperator mobOperator) noexcept;
        void removeMobileOperator(const MobileOperator& mobOperator) noexcept;
        bool editMobileOperator(MobileOperator&& mobOperator) noexcept;

        Country& operator=(const Country &rhs);
        bool operator<(const Country& rhs) const noexcept;
        bool operator<(const int& rhs) const noexcept;
        bool operator==(const Country& rhs) const noexcept;
        bool operator==(const int& rhs) const noexcept;
};


#endif // COUNTRY_H
