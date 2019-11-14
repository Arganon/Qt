#ifndef DAOFACTORY_H
#define DAOFACTORY_H

class Connection;
class QsqldbCountryDao;
class QsqldbMobileOperatorDao;
class SQLConnection;

class DaoFactory
{
    private:
        DaoFactory() noexcept;
        ~DaoFactory() noexcept;
        SQLConnection* m_Connection;

    public:
        static DaoFactory* getInstance() noexcept;
        QsqldbCountryDao* createCountryDao() noexcept;
        QsqldbMobileOperatorDao* createMobileOperatorDao() noexcept;

        DaoFactory(const DaoFactory& factory) = delete;
        DaoFactory(DaoFactory&& factory) = delete;
        DaoFactory& operator=(const DaoFactory& rhsFactory) = delete;
        DaoFactory& operator==(DaoFactory&& rhsFactory) = delete;
};

#endif // DAOFACTORY_H
