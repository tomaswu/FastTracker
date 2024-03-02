#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#define qdb qDebug()


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(960,600);
    this->initconnect();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initconnect(){
    connect(ui->tabWidget,&QTabWidget::currentChanged,this,&MainWindow::setCurrentTabIndex);
    connect(ui->actionNew,&QAction::triggered,this,&MainWindow::new_tag);
    connect(ui->actionImport_Video,&QAction::triggered,this,&MainWindow::import_video);
}


void MainWindow::import_video(){
    if(tabList.size()==0){
        new_tag();
    }
    if(tabList.size()>0){
        tabList[currentTabIndex]->videoPlayer->open();
    }
}


void MainWindow::new_tag()
{
    TabForm *tmp = new TabForm();
    this->tabList.append(tmp);
    ui->tabWidget->addTab(tmp,QString("tab %1").arg(tabList.size()));
    this->currentTabIndex = ui->tabWidget->currentIndex();
}

void MainWindow::setCurrentTabIndex()
{
    this->currentTabIndex = ui->tabWidget->currentIndex();
}

