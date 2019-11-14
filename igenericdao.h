#ifndef IGENERICDAO_H
#define IGENERICDAO_H

#include <QVector>

template <class T>
class IGenericDao
{
    public:
        virtual T find(const T& obj) = 0;
        virtual QVector<T> findAll() = 0;
        virtual bool create(const T& obj) = 0;
        virtual bool update(const T& obj) = 0;
        virtual bool remove(const T& obj) = 0;
};

#endif // IGENERICDAO_H
