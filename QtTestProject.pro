QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    daofactory.cpp \
    databaseupdater.cpp \
    dialogopereditor.cpp \
    entitybuilder.cpp \
    main.cpp \
    country.cpp \
    mainwindow.cpp \
    mobileoperator.cpp \
    qsqldbcountrydao.cpp \
    qsqldbmobileoperatordao.cpp \
    sqlconnection.cpp \
    treeviewmodel.cpp

HEADERS += \
    country.h \
    daofactory.h \
    databaseupdater.h \
    dialogopereditor.h \
    entitybuilder.h \
    ibasedescribeobj.h \
    igenericdao.h \
    mainwindow.h \
    mobileoperator.h \
    qsqldbcountrydao.h \
    qsqldbmobileoperatordao.h \
    sqlconnection.h \
    treeviewmodel.h

FORMS += \
    dialogopereditor.ui \
    mainwindow.ui

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/local/Cellar/sqlite/3.29.0/lib/release/ -lsqlite3.0
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/local/Cellar/sqlite/3.29.0/lib/debug/ -lsqlite3.0
#else:unix: LIBS += -L$$PWD/../../../../../usr/local/Cellar/sqlite/3.29.0/lib/ -lsqlite3.0

#INCLUDEPATH += /usr/local/Cellar/sqlite/3.29.0/include
#DEPENDPATH += /usr/local/Cellar/sqlite/3.29.0/include

RESOURCES += \
    Resource.qrc
