#include "country.h"

Country::Country(const int &mcc, const QString &countryName, const QString &countryCode) noexcept
    : m_Mcc(mcc)
    , m_CountryName(countryName)
    , m_CountryCode(countryCode)
{}

Country::Country(const Country &rhs) {
    m_Mcc = rhs.m_Mcc;
    m_CountryName = rhs.m_CountryName;
    m_CountryCode = rhs.m_CountryCode;
}

int Country::getMcc() const noexcept {
    return m_Mcc;
}

QString Country::getName() const noexcept {
    return m_CountryName;
}

QString Country::getCode() const noexcept {
    return m_CountryCode;
}

QVector<MobileOperator> Country::getMobileOperators() const noexcept {
    return m_MobileOperators;
}

bool Country::addMobileOperator(MobileOperator mobOperator) noexcept {
    if (m_Mcc != mobOperator.getMcc()) {
        return false;
    }
    m_MobileOperators.push_back(mobOperator);
    return true;
}

bool Country::editMobileOperator(MobileOperator&& mobOperator) noexcept {
    if (m_Mcc != mobOperator.getMcc()) {
        return false;
    }
    removeMobileOperator(mobOperator);
    return addMobileOperator(std::move(mobOperator));
}

void Country::removeMobileOperator(const MobileOperator& mobOperator) noexcept {
    m_MobileOperators.removeOne(mobOperator);
}

Country& Country::operator=(const Country &rhs) {
    m_Mcc = rhs.m_Mcc;
    m_CountryName = rhs.m_CountryCode;
    m_CountryCode = rhs.m_CountryCode;
    return *this;
}

bool Country::operator<(const Country& rhs) const noexcept {
    return m_Mcc < rhs.m_Mcc;
}

bool Country::operator<(const int& rhs) const noexcept {
    return m_Mcc < rhs;
}

bool Country::operator==(const Country& rhs) const noexcept {
    return m_Mcc == rhs.m_Mcc;
}

bool Country::operator==(const int& rhs) const noexcept {
    return m_Mcc == rhs;
}
