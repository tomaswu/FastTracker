#include "views/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qRegisterMetaType<cv::Mat>("cv::Mat");
    QApplication a(argc, argv);
    MainWindow mw;
    mw.resize(800, 600);
    mw.show();
    return a.exec();
}
