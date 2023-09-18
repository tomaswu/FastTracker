#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QObject>
#include <opencv2/videoio.hpp>
#include <QSize>
#include <QString>
#include <QFile>
#include <QFileInfo>

class VideoPlayer : public QObject
{
    Q_OBJECT
public:
    explicit VideoPlayer(QObject *parent = nullptr);
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


private:
    //member
    cv::VideoCapture    _video;
    double              _fps{0};

    //method

};

#endif // VIDEOPLAYER_H
