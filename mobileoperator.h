#ifndef MOBILEOPERATOR_H
#define MOBILEOPERATOR_H

#include <QString>
#include "ibasedescribeobj.h"

class MobileOperator {
    private:
        int m_Mcc;
        int m_Mnc;
        QString m_Name;

    public:
        MobileOperator() = default;
        MobileOperator(const int mcc, const int mnc, const QString operatorName) noexcept;
        MobileOperator(const MobileOperator& rhs) noexcept;
        MobileOperator(MobileOperator&& rhs) noexcept;

        int getMcc() const noexcept;
        int getMnc() const noexcept;
        QString getName() const noexcept;
        void setName(const QString& name) noexcept;
        void setMcc(const int mcc) noexcept;
        void setMnc(const int mnc) noexcept;

        MobileOperator& operator=(const MobileOperator& rhs) noexcept;
        MobileOperator& operator=(MobileOperator&& rhs) noexcept = default;
        bool operator<(const MobileOperator& rhs) const noexcept;
        bool operator==(const MobileOperator& rhs) const noexcept;
};

#endif // MOBILEOPERATOR_H
