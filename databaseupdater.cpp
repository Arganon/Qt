#include "databaseupdater.h"
#include "daofactory.h"
#include "entitybuilder.h"
#include "igenericdao.h"
#include "mobileoperator.h"
#include "qsqldbcountrydao.h"
#include "qsqldbmobileoperatordao.h"
#include "treeviewmodel.h"


DataBaseUpdater::DataBaseUpdater() : m_Index(nullptr) {}

DataBaseUpdater::DataBaseUpdater(const QModelIndex* index)
    : m_Index(index) {}

DataBaseUpdater::~DataBaseUpdater() {
//    delete m_Index;
}

bool DataBaseUpdater::updateMobOperatorInDB(const MobileOperator &mobOperator) {
    DaoFactory *daoFactory = DaoFactory::getInstance();
    auto mobOperatorsDao = daoFactory->createMobileOperatorDao();

    return mobOperatorsDao->update(mobOperator);
}

bool DataBaseUpdater::insertMobOperatorToDB(const MobileOperator &mobOperator) {
    DaoFactory *daoFactory = DaoFactory::getInstance();
    auto mobOperatorsDao = daoFactory->createMobileOperatorDao();

    return mobOperatorsDao->create(mobOperator);
}

bool DataBaseUpdater::removeMobOperatorFromDB(const MobileOperator &mobOperator) {
    DaoFactory *daoFactory = DaoFactory::getInstance();
    auto mobOperatorsDao = daoFactory->createMobileOperatorDao();

    return mobOperatorsDao->remove(mobOperator);
}

const QModelIndex& DataBaseUpdater::getModelIndex() const noexcept {
    return *m_Index;
}
