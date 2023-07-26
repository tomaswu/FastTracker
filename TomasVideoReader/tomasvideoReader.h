#ifndef TOMASVIDEOREADER_H
#define TOMASVIDEOREADER_H

#include "TomasVideoReader_global.h"
#include <QObject>
#include <opencv2/highgui.hpp>
#include <QImage>
#include <QTimer>
#include <string>
#include <vector>
#include <QQuickImageProvider>

class TOMASVIDEOREADER_EXPORT TomasVideoReader : public QObject
{
    Q_OBJECT
public:
    explicit TomasVideoReader(QObject *parent = nullptr);
    ~TomasVideoReader();

    //member
    QString                             videoName;
    int                                 rec_method;
    cv::VideoCapture                    *video_reader;
    cv::Mat                             img;
    int                                 pos;
    int                                 beginPos;
    int                                 endPos;
    int                                 recPos;
    double                              play_speed;
    bool                                recFlag=false;
    bool                                needScale=false;

    QTimer                              *play_timer;

    std::string                          testfile="C:\\Users\\Tomas Wu\\Videos\\202203151103光镊演示.mp4";

    bool                                cali_flag=false;
    cv::Size2i                          correctSize;
    cv::Mat                             correctedMat;
    cv::Mat                             mapx;
    cv::Mat                             mapy;
    cv::Matx33d                         intrinsics_matrix;
    cv::Vec4d                           distortion_coeff;

    //method
    cv::Mat                             QImage2Mat(QImage const& image);
    QImage                              Mat2QImage(cv::Mat const& mat);

    Q_INVOKABLE double                  getFps();
    Q_INVOKABLE int                     getPos();
    Q_INVOKABLE bool                    setPos(int i);
    Q_INVOKABLE int                     getBeginPos();
    Q_INVOKABLE void                    setBeginPos(int i);
    Q_INVOKABLE int                     getEndPos();
    Q_INVOKABLE void                    setEndPos(int i);
    Q_INVOKABLE int                     getFrameCount();
    Q_INVOKABLE void                    open(QString path);
    Q_INVOKABLE void                    close();
    Q_INVOKABLE bool                    isOpened();
    void                                getFrame();
    Q_INVOKABLE void                    reloadFrame();
    Q_INVOKABLE void                    setPlaySpeed(double speed);
    Q_INVOKABLE void                    play_pause();
    Q_INVOKABLE bool                    isPlaying(){return play_timer->isActive();};
    Q_INVOKABLE QList<int>              getImageSize();


    bool                                initUndistort(cv::MatSize size);
    Q_INVOKABLE void                    setCaliFlag(bool flag);
    bool                                readCameraMatrix(cv::Matx33d &K,cv::Vec4d &D);

    // qml read
    Q_PROPERTY(int pos MEMBER pos NOTIFY posChanged);


signals:
    void posChanged();
    void alreadyOpened();
    void imgReady(cv::Mat img);
};


#endif // TOMASVIDEOREADER_H
