#include "utils.h"

utils::utils(QObject *parent)
    : QObject{parent}
{

}

QImage utils::Mat2QImage(const cv::Mat &mat)
{
    cv::Mat temp;
    cv::cvtColor(mat, temp,cv::COLOR_BGR2RGB);
    QImage image((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    image.bits();
    return image;
}

cv::Mat utils::QImage2Mat(const QImage &image)
{
    cv::Mat tmp(image.height(),image.width(),CV_8UC3,(uchar*)image.bits(),image.bytesPerLine());
    cv::Mat mat;
    cv::cvtColor(tmp, mat,cv::COLOR_BGR2RGB);
    return mat;
}
