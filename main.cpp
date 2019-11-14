#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <iostream>

#include "country.h"
#include "daofactory.h"
#include "entitybuilder.h"
#include "igenericdao.h"
#include "mobileoperator.h"
#include "qsqldbcountrydao.h"
#include "qsqldbmobileoperatordao.h"
#include "sqlconnection.h"
#include "ibasedescribeobj.h"

void tests();

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
