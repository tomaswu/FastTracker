#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QObject>
#include <QSize>
#include <QString>
#include <QFile>
#include <QFileInfo>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/imgproc_c.h>

#include <QMetaType>

int _r = qRegisterMetaType<cv::Mat>("cv::Mat");

class VideoPlayer : public QObject
{
    Q_OBJECT
public:
    explicit VideoPlayer(QObject *parent = nullptr);
    ~VideoPlayer();
    void        open(QString path="");
    void        close();
    int         pos();
    cv::Mat     backward();
    cv::Mat     next();
    void        setPos(int pos);
    bool        isOpened();
    int         frameCount();
    double      fps();
    QSize       getFrameSize();

signals:
    void imgReady(cv::Mat img);

private:
    //member
    cv::VideoCapture    *_video;
    double              _fps{0};
    QSize               _imgSize{0,0};
    //method

};

#endif // VIDEOPLAYER_H
