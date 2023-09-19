#include "tabform.h"
#include "ui_tabform.h"

#include "utils/utils.h"

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

void TabForm::initConnections()
{
    connect(videoPlayer,&VideoPlayer::imgReady,this,&TabForm::showFrame);
}
