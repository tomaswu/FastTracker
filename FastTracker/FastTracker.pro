QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += debug_and_release

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    utils/historymanager.cpp \
    utils/mtypes.cpp \
    utils/utils.cpp \
    video/videoplayer.cpp \
    views/dialogvideogoto.cpp \
    views/mainwindow.cpp \
    views/tabform.cpp \
    views/tchartview.cpp \
    views/tchartwindow.cpp

HEADERS += \
    utils/historymanager.h \
    utils/mtypes.h \
    utils/utils.h \
    video/videoplayer.h \
    views/dialogvideogoto.h \
    views/mainwindow.h \
    views/tabform.h \
    views/tchartview.h \
    views/tchartwindow.h

FORMS += \
    views/dialogvideogoto.ui \
    views/mainwindow.ui \
    views/tabform.ui

windows{
    INCLUDEPATH += E:\Tomas_temp\opencv\opencv480\opencv\build\include \
                   C:\embedded_python\include \
                   E:\boost_1_81_0\boost_1_81_0


LIBS += -LE:\boost_1_81_0\boost_1_81_0\bin.v2\libs\python\build\msvc-14.3\release\link-static\python-3.11\threading-multi \
        -LE:\boost_1_81_0\boost_1_81_0\bin.v2\libs\python\build\msvc-14.3\debug\link-static\python-3.11\threading-multi \
        -LE:\Tomas_temp\opencv\opencv480\opencv\build\x64\vc16\lib \
        -LC:\embedded_python\libs

    CONFIG(debug,debug|release){
        LIBS += -lopencv_world480d -lpython311 -llibboost_python311-vc143-mt-gd-x64-1_81 -llibboost_numpy311-vc143-mt-gd-x64-1_81
    }
    CONFIG(release,debug|release){
        LIBS += -lopencv_world480 -lpython311 -lboost_python311-vc143-mt-x64-1_81 -lboost_numpy311-vc143-mt-x64-1_81
    }
}

macx{
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 12.0
    INCLUDEPATH += /opt/homebrew/Cellar/opencv/4.5.5/include/opencv4 \
                   /Library/Frameworks/Python.framework/Versions/3.10/include/python3.10 \
                   /Users/tomaswu/usr/boost_1_79_0

    LIBS += -L/opt/homebrew/Cellar/opencv/4.5.5/lib -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_highgui -lopencv_videoio -lopencv_calib3d
    LIBS += -L/Library/Frameworks/Python.framework/Versions/3.10/lib -lpython3.10
    LIBS += -L/Users/tomaswu/usr/boost_1_79_0/stage/lib -lboost_python310 -lboost_numpy310
#    QMAKE_POST_LINK += cp $$PWD/python_scripts/data_process.py $$OUT_PWD/data_process.py

}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/res.qrc

DISTFILES += \
    pyplugin/plugin_main.py

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../TomasCommandLineTools/release/ -lTomasCommandLineTools
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../TomasCommandLineTools/debug/ -lTomasCommandLineTools
else:unix: LIBS += -L$$OUT_PWD/../TomasCommandLineTools/ -lTomasCommandLineTools

INCLUDEPATH += $$PWD/../TomasCommandLineTools
DEPENDPATH += $$PWD/../TomasCommandLineTools
