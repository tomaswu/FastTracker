#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QImage>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

class utils : public QObject
{
    Q_OBJECT
public:
    explicit utils(QObject *parent = nullptr);

    static QImage Mat2QImage(cv::Mat const& mat);
    static cv::Mat QImage2Mat(QImage const& image);

signals:

};

#endif // UTILS_H
