#include "tabform.h"
#include "ui_tabform.h"
#include "utils/utils.h"
#include <QDebug>
#include <QMouseEvent>
#include <QCursor>
#include <QActionGroup>
#include <QMessageBox>
#include <QInputDialog>

#define qdb qDebug()

TabForm::TabForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabForm)
{
    ui->setupUi(this);
    videoPlayer = new VideoPlayer;
    scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);
    imgItem = new QGraphicsPixmapItem();
    scene->addItem(imgItem);
    initConnections();

}

TabForm::~TabForm()
{
    delete ui;
}

void TabForm::showFrame(cv::Mat mat)
{
    auto qimg = utils::Mat2QImage(mat);
    imgItem->setPixmap(QPixmap::fromImage(qimg));
}

void TabForm::setZoomRatio()
{
    double v = ui->spinBox_zoom->value()/100.0;
    this->imgItem->setScale(v);
    qdb<<"set zoom:"<<v;
}

void TabForm::setVideoPos(int v)
{
    auto obj = sender()->objectName();
    if(obj=="horizontalSlider"){
        videoPlayer->setPos(v);
    }
    else if(obj=="toolButton_back"){
        videoPlayer->backward();
        ui->horizontalSlider->setValue(videoPlayer->pos());
    }
    else if(obj=="toolButton_next"){
        videoPlayer->next();
        ui->horizontalSlider->setValue(videoPlayer->pos());
    }

    // ***show pos***
   int fpos = videoPlayer->pos();
   _pos.setFrame(fpos);
   _showCurrentPos();
}

void TabForm::video_goto(mtypes::VideoPos *pos)
{
    this->setVideoPos(pos->frame());
}

void TabForm::initConnections()
{
    connect(videoPlayer,&VideoPlayer::imgReady,this,&TabForm::showFrame);
    connect(ui->spinBox_zoom,&QSpinBox::valueChanged,this,&TabForm::setZoomRatio);
    connect(ui->toolButton_next,&QToolButton::clicked,this,&TabForm::setVideoPos);
    connect(ui->toolButton_back,&QToolButton::clicked,this,&TabForm::setVideoPos);
    connect(videoPlayer,&VideoPlayer::getVideoInfo,this,[=](int mf,double fps){this->_pos.setInfo(mf,fps);
                                                            ui->horizontalSlider->setMaximum(mf);});
    connect(ui->horizontalSlider,&QSlider::sliderMoved,this,&TabForm::setVideoPos);

    //frame menu init
    _createFrameMenu();

}

void TabForm::_createFrameMenu()
{
    QActionGroup *gp = new QActionGroup(this);
    QMenu *tmpMenu = new QMenu();
    tmpMenu->setTitle("显示");

    QAction *ac = new QAction();
    ac->setText("帧");
    ac->setCheckable(true);
    tmpMenu->addAction(ac);
    gp->addAction(ac);
    ac->setChecked(true);
    connect(ac,&QAction::triggered,this,[=](){this->_pos.setPosType(mtypes::POS_TYPE::frame);});

    ac = new QAction();
    ac->setText("时间");
    ac->setCheckable(true);
    tmpMenu->addAction(ac);
    gp->addAction(ac);
    connect(ac,&QAction::triggered,this,[=](){this->_pos.setPosType(mtypes::POS_TYPE::time);});

    ac = new QAction();
    ac->setText("步骤");
    ac->setCheckable(true);
    tmpMenu->addAction(ac);
    gp->addAction(ac);
    connect(ac,&QAction::triggered,this,[=](){this->_pos.setPosType(mtypes::POS_TYPE::step);});

    _frameMenu.addMenu(tmpMenu);
    gp->setExclusive(true);

    ac = new QAction();
    ac->setText("当前时间设置为0");
    _frameMenu.addAction(ac);
    connect(ac,&QAction::triggered,this,[=](){this->_pos.setCurrentFrame2ZeroTime();this->_showCurrentPos();});

    ac = new QAction();
    ac->setText("设置时间");
    _frameMenu.addAction(ac);
    connect(ac,&QAction::triggered,this,[=](){this->_setPosTime();});

    ac = new QAction();
    ac->setText("跳转");
    _frameMenu.addAction(ac);

    connect(ui->toolButton_pos,&QToolButton::clicked,this,[=](){_frameMenu.popup(QCursor::pos());});
}

void TabForm::_showCurrentPos()
{
    QString s;
    if(_pos.posType()!=mtypes::POS_TYPE::time){
        s=QString::number(_pos.getTypePos(),'f',0);
    }
    else{
        s=QString::number(_pos.getTypePos(),'f',3);
    }
    ui->toolButton_pos->setText(s);
}

void TabForm::_setPosTime()
{
    bool ok{false};
    auto d = QInputDialog::getDouble(this,tr("input time"),tr("input a value (s) as current time:"),0,-99999999,99999999,3,&ok);
    if(ok){
        _pos.setTime(d);
    }
}

















