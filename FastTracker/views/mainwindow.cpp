#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initconnect(){
    connect(ui->actionImport_Video,&QAction::triggered,this,&MainWindow::import_video);

}


void MainWindow::import_video(){
    if(tabList.size()>0){
    }
    tabList[currentTabIndex]->videoPlayer->open();



}

void MainWindow::new_tag()
{
    auto tmp = new TabForm();
    this->tabList.append(tmp);
    ui->tabWidget->addTab(tmp);

}

