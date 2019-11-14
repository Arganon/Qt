#ifndef DATABASEUPDATER_H
#define DATABASEUPDATER_H

#include "country.h"
#include "mobileoperator.h"
#include <QModelIndex>

class DataBaseUpdater
{
    private:
        const QModelIndex* m_Index;

    public:
        DataBaseUpdater();
        ~DataBaseUpdater();
        explicit DataBaseUpdater(const QModelIndex* index);
        bool updateMobOperatorInDB(const MobileOperator &mobOperator);
        bool insertMobOperatorToDB(const MobileOperator &mobOperator);
        bool removeMobOperatorFromDB(const MobileOperator &mobOperator);
        const QModelIndex& getModelIndex() const noexcept;
};

#endif // DATABASEUPDATER_H
