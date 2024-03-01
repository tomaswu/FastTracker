#ifndef TOMASCOMMANDLINETOOLS_H
#define TOMASCOMMANDLINETOOLS_H

#include <QObject>
#include <QProcess>
#include <QString>
#include <QThread>

namespace tsh {


class TomasCommandLineTools:public QObject
{
    Q_OBJECT
public:
    explicit TomasCommandLineTools(QObject *parent = nullptr);
    ~TomasCommandLineTools();
    //member
    QProcess            *p;

    //method
    void            system(QString s);
    QString         getSaveFileName(QString title,QString dir,QString filter);
    QString         getOpenFileName(QString title,QString dir,QString filter);
    QString         getFolderFromFilePath(QString path);
    QString         getExistingFolder(QString title,QString dir);
    QString         getNewNameByTime(QString dic,QString tail);
    QString         getDirByFilePaht(QString filepath);
    void            openFile(QString file);

signals:

};

}// end namespace
#endif // TOMASCOMMANDLINETOOLS_H
