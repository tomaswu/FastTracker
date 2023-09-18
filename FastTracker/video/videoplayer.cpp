#include "videoplayer.h"
#include "QFileDialog"
#include <QDebug>

#define qdb qDebug()


VideoPlayer::VideoPlayer(QObject *parent)
    : QObject{parent}
{
    this->_video = new cv::VideoCapture;
}

VideoPlayer::~VideoPlayer()
{
    this->_video->release();
    delete this->_video;
}

void VideoPlayer::open(QString path)
{
    if(path.size()==0){
        path = QFileDialog::getOpenFileName(nullptr,tr("open video"),"./","*.mp4|*.avi");
        qdb<<path;
    }
    this->_video->open(path.toStdString());
}

void VideoPlayer::close()
{

}

int VideoPlayer::pos()
{
    return -1;
}

cv::Mat VideoPlayer::backward()
{
    cv::Mat img;
    return img;
}

cv::Mat VideoPlayer::next()
{
    cv::Mat img;
    return img;
}

void VideoPlayer::setPos(int pos)
{

}

bool VideoPlayer::isOpened()
{
    return false;
}

int VideoPlayer::frameCount()
{
    return 0;
}

double VideoPlayer::fps()
{
    return this->_fps;
}

QSize VideoPlayer::getFrameSize()
{
    return this->_imgSize;
}
