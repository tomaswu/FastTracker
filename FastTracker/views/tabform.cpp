#include "tabform.h"
#include "ui_tabform.h"
#include "utils/utils.h"
#include <QDebug>
#include <QMouseEvent>
#include <QCursor>
#include <QActionGroup>

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

    //frame menu init
    _createFrameMenu();
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

void TabForm::setMaxFrameValue(int value)
{
    ui->horizontalSlider->setMaximum(value);
    ui->toolButton_frame->setText(QString::number(value));
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
    ui->toolButton_currentPos->setText(QString::number(videoPlayer->pos()));
}

void TabForm::initConnections()
{
    connect(videoPlayer,&VideoPlayer::imgReady,this,&TabForm::showFrame);
    connect(ui->spinBox_zoom,&QSpinBox::valueChanged,this,&TabForm::setZoomRatio);
    connect(ui->toolButton_next,&QToolButton::clicked,this,&TabForm::setVideoPos);
    connect(ui->toolButton_back,&QToolButton::clicked,this,&TabForm::setVideoPos);
    connect(videoPlayer,&VideoPlayer::getFramesCount,this,&TabForm::setMaxFrameValue);
    connect(ui->horizontalSlider,&QSlider::valueChanged,this,&TabForm::setVideoPos);
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

    ac = new QAction();
    ac->setText("时间");
    ac->setCheckable(true);
    tmpMenu->addAction(ac);
    gp->addAction(ac);

    ac = new QAction();
    ac->setText("步骤");
    ac->setCheckable(true);
    tmpMenu->addAction(ac);
    gp->addAction(ac);

    _frameMenu.addMenu(tmpMenu);
    gp->setExclusive(true);

    ac = new QAction();
    ac->setText("当前时间设置为0");
    _frameMenu.addAction(ac);

    ac = new QAction();
    ac->setText("设置时间");
    _frameMenu.addAction(ac);

    ac = new QAction();
    ac->setText("跳转");
    _frameMenu.addAction(ac);

    connect(ui->toolButton_frame,&QToolButton::clicked,this,[=](){_frameMenu.popup(QCursor::pos());});
}

















