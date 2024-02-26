#ifndef TOMASCOMMANDLINETOOLS_H
#define TOMASCOMMANDLINETOOLS_H

#include "TomasCommandLineTools_global.h"
#include <QObject>
#include <QProcess>
#include <QString>
#include <QThread>

namespace tsh {


class TOMASCOMMANDLINETOOLS_EXPORT TomasCommandLineTools:public QObject
{
    Q_OBJECT
public:
    explicit TomasCommandLineTools(QObject *parent = nullptr);
    ~TomasCommandLineTools();
    //member
    QProcess            *p;

    //method
    Q_INVOKABLE void            system(QString s);
    Q_INVOKABLE QString         getSaveFileName(QString title,QString dir,QString filter);
    Q_INVOKABLE QString         getOpenFileName(QString title,QString dir,QString filter);
    Q_INVOKABLE QString         getFolderFromFilePath(QString path);
    Q_INVOKABLE QString         getExistingFolder(QString title,QString dir);
    Q_INVOKABLE QString         getNewNameByTime(QString dic,QString tail);
    Q_INVOKABLE QString         getDirByFilePaht(QString filepath);
    Q_INVOKABLE void            openFile(QString file);

signals:


};



}// end namespace
#endif // TOMASCOMMANDLINETOOLS_H
