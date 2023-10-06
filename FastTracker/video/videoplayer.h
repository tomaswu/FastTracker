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

class VideoPlayer : public QObject
{
    Q_OBJECT
public:
    explicit VideoPlayer(QObject *parent = nullptr);
    ~VideoPlayer();
    void        open(QString path="");
    void        close();
    void        readFrame();
    int         pos();
    void        backward();
    void        next();
    void        setPos(int p);
    bool        isOpened();
    int         frameCount();
    double      fps();
    QSize       getFrameSize();

signals:
    void imgReady(cv::Mat img);
    void getVideoInfo(int maxFrame,double fps);
    void errorOccured(QString err);

private:
    //member
    cv::VideoCapture    *_video{nullptr};
    double              _fps{0};
    QSize               _imgSize{0,0};
    cv::Mat             _mat;
    //method

};

#endif // VIDEOPLAYER_H
