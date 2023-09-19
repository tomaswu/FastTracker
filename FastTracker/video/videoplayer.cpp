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
        path = QFileDialog::getOpenFileName(nullptr,tr("open video"),"./","*.mp4;*.avi");
    }
    this->_video->open(path.toStdString());
    if(_video->isOpened())readFrame();
}

void VideoPlayer::close()
{

}

void VideoPlayer::readFrame()
{
    if(_video==nullptr){
        emit errorOccured("read frame but video not opened!");
        return;
    }
    if(_video->isOpened()){
        bool ret = _video->read(_mat);
        if(ret){
            emit imgReady(_mat);
        }else{
            emit errorOccured("read frame error!");
        }
    }else{
        emit errorOccured("read frame but video not opened!");
    }
}

int VideoPlayer::pos()
{
    if(_video==nullptr)return -1;
    if(!_video->isOpened())return -1;
    return _video->get(cv::CAP_PROP_POS_FRAMES);
}

void VideoPlayer::backward()
{
    if(_video==nullptr)return;
    if(_video->isOpened()){
        auto p = pos();
        p = p - 2;
        if(p<0)p=0;
        _video->set(cv::CAP_PROP_POS_FRAMES,p);
        readFrame();
    }
}

void VideoPlayer::next()
{
    if(_video==nullptr)return;
    if(_video->isOpened()){
        readFrame();
    }
}

void VideoPlayer::setPos(int p)
{
    if(_video==nullptr)return;
    if(_video->isOpened()){
        if(p<0)p=0;
        auto count = _video->get(cv::CAP_PROP_FRAME_COUNT);
        if(p>=count)p=count-1;
        _video->set(cv::CAP_PROP_POS_FRAMES,p);
        readFrame();
    }
}

bool VideoPlayer::isOpened()
{
    if(_video==nullptr)return false;
    return _video->isOpened();
}

int VideoPlayer::frameCount()
{
    if(_video==nullptr)return 0;
    return _video->get(cv::CAP_PROP_FRAME_COUNT);
}

double VideoPlayer::fps()
{
    if(_video==nullptr)return -1;
    return _video->get(cv::CAP_PROP_FPS);
}

QSize VideoPlayer::getFrameSize()
{
    return this->_imgSize;
}
