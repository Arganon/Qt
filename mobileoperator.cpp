#include "mobileoperator.h"

MobileOperator::MobileOperator(const int mcc, const int mnc, const QString name) noexcept
    : m_Mcc(mcc)
    , m_Mnc(mnc)
    , m_Name(name)
{}
MobileOperator::MobileOperator(const MobileOperator& rhs) noexcept
    : m_Mcc(rhs.m_Mcc)
    , m_Mnc(rhs.m_Mnc)
    , m_Name(rhs.m_Name) {}

MobileOperator::MobileOperator(MobileOperator&& rhs) noexcept
    : m_Mcc(std::move(rhs.m_Mcc))
    , m_Mnc(std::move(rhs.m_Mnc))
    , m_Name(std::move(rhs.m_Name)) {}

int MobileOperator::getMcc() const noexcept {
    return m_Mcc;
}

int MobileOperator::getMnc() const noexcept {
    return m_Mnc;
}

QString MobileOperator::getName() const noexcept {
    return m_Name;
}

void MobileOperator::setName(const QString &name) noexcept {
    m_Name = name;
}

void MobileOperator::setMcc(const int mcc) noexcept {
    m_Mcc = mcc;
}

void MobileOperator::setMnc(const int mnc) noexcept {
    m_Mnc = mnc;
}

MobileOperator& MobileOperator::operator=(const MobileOperator &rhs) noexcept {
    m_Mcc = rhs.m_Mcc;
    m_Mnc = rhs.m_Mnc;
    m_Name = rhs.m_Name;
    return *this;
}

bool MobileOperator::operator<(const MobileOperator& rhs) const noexcept {
    return m_Mnc < rhs.m_Mnc && m_Mcc < rhs.m_Mcc;
}

bool MobileOperator::operator==(const MobileOperator& rhs) const noexcept {
    return m_Mnc == rhs.m_Mnc && m_Mcc == rhs.m_Mcc;
}
