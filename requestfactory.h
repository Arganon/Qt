#ifndef REQUESTFACTORY_H
#define REQUESTFACTORY_H

template <typename T>
class RequestFactory
{
public:
    T build() = 0;
};

#endif // REQUESTFACTORY_H
