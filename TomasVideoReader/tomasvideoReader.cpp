#include "tomasvideoReader.h"
#include <string>
#include <vector>
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/calib3d.hpp>
#include <string>
#include <fstream>

TomasVideoReader::TomasVideoReader(QObject *parent)
    : QObject{parent}
{

    video_reader = new cv::VideoCapture;
    play_timer = new QTimer;

    connect(this->play_timer,&QTimer::timeout,this,&TomasVideoReader::getFrame);
    play_timer->setInterval(5);

//    this->open(this->testfile);
}

TomasVideoReader::~TomasVideoReader(){
    play_timer->stop();
    delete play_timer;
    video_reader->release();
    delete video_reader;
}

void TomasVideoReader::open(QString path){
    if(play_timer->isActive())
    {
        play_timer->stop();
    }
    if(video_reader->isOpened()){
        video_reader->release();
    }
    video_reader->open(path.toStdString());
    if (video_reader->isOpened()){
        setPlaySpeed(1.0);
        getPos();
        setBeginPos(0);
        setEndPos(getFrameCount());
        getFrame();
        emit alreadyOpened();
    }
}

void TomasVideoReader::close(){
    play_timer->stop();
    if(video_reader->isOpened()){
        video_reader->release();
    }
}

int TomasVideoReader::getPos(){
    int p = video_reader->get(cv::CAP_PROP_POS_FRAMES);
    if (p!=pos){
        emit posChanged();
    }
    pos=p;
    return pos;
}

bool TomasVideoReader::setPos(int i){
    bool ret;
    video_reader->set(cv::CAP_PROP_POS_FRAMES,i);
    this->getFrame();
    ret = video_reader->set(cv::CAP_PROP_POS_FRAMES,i);
    if (ret){
        pos=i;
        emit posChanged();
    }
    return ret;
}

void TomasVideoReader::reloadFrame(){
    this->setPos(this->pos-1);
    this->getFrame();
}


int TomasVideoReader::getBeginPos(){
    return 0;
}

void TomasVideoReader::setBeginPos(int i){
    this->beginPos = i;
}

int TomasVideoReader::getEndPos(){
    return 0;
}

void TomasVideoReader::setEndPos(int i){
    this->endPos=i;
}

int TomasVideoReader::getFrameCount(){
    return video_reader->get(cv::CAP_PROP_FRAME_COUNT);
}

bool TomasVideoReader::isOpened(){
    return video_reader->isOpened();
}


bool TomasVideoReader::initUndistort(cv::MatSize size){
    this->correctSize.width=size[1];
    this->correctSize.height=size[0];
    readCameraMatrix(this->intrinsics_matrix,this->distortion_coeff);
    cv::fisheye::initUndistortRectifyMap(intrinsics_matrix, distortion_coeff, cv::Matx33d::eye(), intrinsics_matrix, correctSize, CV_16SC2, mapx, mapy);
    return true;

}

void TomasVideoReader::setCaliFlag(bool flag){
    this->cali_flag=flag;
    if(flag && !this->img.empty()){
        initUndistort(this->img.size);
    }
}

void TomasVideoReader::getFrame(){
    bool ret = video_reader->read(img);
    if(!ret){
        return;
    }
    if (cali_flag){
        if(correctSize.width!=img.size[1] || correctSize.height!=img.size[0]){
            initUndistort(img.size);
        }
        cv::remap(img, correctedMat, mapx, mapy, cv::INTER_LINEAR, cv::BORDER_DEFAULT);
        img=correctedMat;
    }

    emit imgReady(img);
    getPos();
    if(pos>=endPos && play_timer->isActive()){
        setPos(beginPos);
    }
}


void TomasVideoReader::setPlaySpeed(double speed){
    play_speed = speed;
    int fps = video_reader->get(cv::CAP_PROP_FPS);
    double itv = 1000/(fps*speed);
    int new_time = itv;
    play_timer->setInterval(new_time);
}

void TomasVideoReader::play_pause(){
    if(play_timer->isActive()){
        play_timer->stop();
    }
    else{
        play_timer->start();
    }
}

double TomasVideoReader::getFps(){
   return video_reader->get(cv::CAP_PROP_FPS);
}

QList<int> TomasVideoReader::getImageSize(){
    QList<int> size;
    size.append(img.size().width);
    size.append(img.size().height);
    return size;
}


QImage TomasVideoReader::Mat2QImage(cv::Mat const& mat)
{
    cv::Mat temp;
    cv::cvtColor(mat, temp,cv::COLOR_BGR2RGB);
    QImage image((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    image.bits();
    return image;
}

cv::Mat TomasVideoReader::QImage2Mat(QImage const& image)
{
    cv::Mat tmp(image.height(),image.width(),CV_8UC3,(uchar*)image.bits(),image.bytesPerLine());
    cv::Mat mat;
    cv::cvtColor(tmp, mat,cv::COLOR_BGR2RGB);
    return mat;
}


bool TomasVideoReader::readCameraMatrix(cv::Matx33d &K,cv::Vec4d &D){
    std::ifstream camera_matrix("cameraMatrix");
    if(!camera_matrix.is_open()){
        return false;
    }
    double tmp;
    int n=0;
    while(camera_matrix>>tmp){
        if (n<9){
             K(n/3,n%3)=tmp;
        }
        else{
           D((n-9)%4)=tmp;
        }
        n+=1;
    }
    if (n>13){
        return false;
    }
    return true;
}



