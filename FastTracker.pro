QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    utils/utils.cpp \
    video/videoplayer.cpp \
    views/mainwindow.cpp \
    views/tabform.cpp \
    views/tchartview.cpp \
    views/tchartwindow.cpp

HEADERS += \
    utils/utils.h \
    video/videoplayer.h \
    views/mainwindow.h \
    views/tabform.h \
    views/tchartview.h \
    views/tchartwindow.h

FORMS += \
    views/mainwindow.ui \
    views/tabform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/res.qrc

DISTFILES += \
    pyplugin/plugin_main.py
