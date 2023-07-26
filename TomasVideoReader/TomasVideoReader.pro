QT += core quick

TEMPLATE = lib
DEFINES += TOMASVIDEOREADER_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    tomasvideoReader.cpp

HEADERS += \
    TomasVideoReader_global.h \
    tomasvideoReader.h

windows{

    INCLUDEPATH += \
        E:\Tomas_temp\opencv\opencv460\opencv\build\include

    LIBS += -LE:\Tomas_temp\opencv\opencv460\opencv\build\x64\vc15\lib

    CONFIG(debug,debug|release){
        LIBS += -lopencv_world460d
    }
    CONFIG(release,debug|release){
        LIBS += -lopencv_world460
    }
}

# for win11 on mac
#windows{

#    INCLUDEPATH += "C:\Users\tomaswu\myprograms\opencv\build\include"

#    LIBS += -LC:\Users\tomaswu\myprograms\opencv\build\x64\vc14\lib

#    CONFIG(debug,debug|release){
#        LIBS += -lopencv_world460d
#    }
#    CONFIG(release,debug|release){
#        LIBS += -lopencv_world460
#    }
#}


macx{
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 12.0
    INCLUDEPATH += /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/13.1.6/include \
                   /opt/homebrew/Cellar/opencv/4.5.5/include/opencv4
    LIBS += -L/opt/homebrew/Cellar/opencv/4.5.5/lib -lopencv_core -lopencv_imgproc \
            -lopencv_imgcodecs -lopencv_highgui -lopencv_videoio -lopencv_calib3d
}



# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
