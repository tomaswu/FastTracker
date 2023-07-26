#include "tomascommandlinetools.h"
#include <QProcess>
#include <QString>
#include <QFileDialog>
#include <QFileInfo>
#include <iostream>
#include <QDesktopServices>
#include <QUrl>
#include <time.h>

namespace tsh {


TomasCommandLineTools::TomasCommandLineTools(QObject *parent)
    :QObject{parent}
{
    p = new QProcess;
}

TomasCommandLineTools::~TomasCommandLineTools(){
    delete p;
}


void TomasCommandLineTools::system(QString s){
    p->startCommand(s);
}

QString TomasCommandLineTools::getSaveFileName(QString title,QString dir,QString filter){
    auto s  = QFileDialog::getSaveFileName(nullptr,title,dir,filter);
    return s;
}

QString TomasCommandLineTools::getOpenFileName(QString title,QString dir,QString filter){
    auto s = QFileDialog::getOpenFileName(nullptr,title,dir,filter);
    return s;
}

QString TomasCommandLineTools::getFolderFromFilePath(QString path){
    QFileInfo f(path);
    return f.dir().absolutePath();
}

QString TomasCommandLineTools::getExistingFolder(QString title,QString dir){
    auto s = QFileDialog::getExistingDirectory(nullptr,title,dir);
    return s;
}

QString TomasCommandLineTools::getNewNameByTime(QString dic,QString tail){
    time_t t;
    tm tinfo;
    time(&t);
    #ifdef Q_OS_WINDOWS
    localtime_s(&tinfo,&t);
    #elif defined Q_OS_MACOS
    localtime_r(&t,&tinfo);
    #endif
    if(!dic.endsWith('/')){
        dic.append("/");
    }
    if(!tail.startsWith(".")){
        tail="."+tail;
    }
    auto s=dic+QString("%1_%2_%3_%4_%5_%6").arg(tinfo.tm_year+1900).arg(tinfo.tm_mon+1).arg(tinfo.tm_mday).arg(tinfo.tm_hour).arg(tinfo.tm_min).arg(tinfo.tm_sec);
    return s+tail;
}


QString TomasCommandLineTools::getDirByFilePaht(QString filepath){
    QFileInfo f(filepath);
    return f.path();
}

void TomasCommandLineTools::openFile(QString file){
    QDesktopServices::openUrl(QUrl::fromLocalFile(file));
}



}//end namespace
