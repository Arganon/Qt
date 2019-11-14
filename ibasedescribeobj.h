#ifndef IBASEDESCRIBEOBJ_H
#define IBASEDESCRIBEOBJ_H

#include <QString>

class IBaseDescribeObj
{
public:
    virtual ~IBaseDescribeObj() {}
    virtual int getMcc() const noexcept = 0;
    virtual QString getName() const noexcept = 0;
//    virtual QString getCode() const noexcept;
//    virtual int getMnc() const noexcept;
//    virtual void changeMobOperName(const QString& name) noexcept;


};

#endif // IBASEDESCRIBEOBJ_H
