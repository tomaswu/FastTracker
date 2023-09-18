#include "videoplayer.h"
#include "QFileDialog"
#include <QDebug>

#define qdb qDebug()


VideoPlayer::VideoPlayer(QObject *parent)
    : QObject{parent}
{

}

void VideoPlayer::open(QString path)
{
    if(path.size()==0){
        path = QFileDialog::getOpenFileName(nullptr,tr("open video"),"./","*.mp4|*.avi");
        qdb<<path;
    }
    this->_video.open(path.toStdString());
}
