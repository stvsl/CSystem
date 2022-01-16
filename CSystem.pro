QT       += core gui network sql webenginewidgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    configManager/configmanager.cpp \
    csystemmain/accountmanagement.cpp \
    csystemmain/dataview.cpp \
    csystemmain/mapsetting.cpp \
    csystemmain/csystemmain.cpp \
    csystemmain/mapview.cpp \
    csystemmain/nodeinformation.cpp \
    csystemmain/nodeinstall.cpp \
    csystemmain/servicecontrol.cpp \
    csystemmain/serviceimformation.cpp \
    csystemmain/systemsetting.cpp \
    main.cpp \
    netWorkUtils/netWorkUtils.cpp\
    DButils/dbutils.cpp\

HEADERS += \
    configManager/configmanager.h \
    configManager/mapconfig.h \
    csystemmain/accountmanagement.h \
    csystemmain/dataview.h \
    csystemmain/mapsetting.h \
    csystemmain/csystemmain.h \
    csystemmain/mapview.h \
    csystemmain/nodeinformation.h \
    csystemmain/nodeinstall.h \
    csystemmain/servicecontrol.h \
    csystemmain/serviceimformation.h \
    csystemmain/systemsetting.h \
    main.h \
    netWorkUtils/netWorkUtils.h\
    DButils/dbutils.h\

FORMS += \
    csystemmain/accountmanagement.ui \
    csystemmain/csystemmain.ui \
    csystemmain/dataview.ui \
    csystemmain/mapsetting.ui \
    csystemmain/mapview.ui \
    csystemmain/nodeinformation.ui \
    csystemmain/nodeinstall.ui \
    csystemmain/servicecontrol.ui \
    csystemmain/serviceimformation.ui \
    csystemmain/systemsetting.ui

TRANSLATIONS += \
    CSystem_zh_CN.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    sourceimg.qrc
