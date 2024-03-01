#include "views/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qRegisterMetaType<cv::Mat>("cv::Mat");
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(800, 600);
    w.show();
    return a.exec();
}
