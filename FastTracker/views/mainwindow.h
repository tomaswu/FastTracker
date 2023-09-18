#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tabform.h"
#include "utils/historymanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QList<TabForm *>        tabList;                //save the tab widget pointer
    int                     currentTabIndex{-1};

    //method
    void                    initconnect();
    void                    import_video();
    void                    new_tag();
    void                    setCurrentTabIndex();

};
#endif // MAINWINDOW_H
