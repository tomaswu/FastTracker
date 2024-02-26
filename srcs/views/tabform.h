#ifndef TABFORM_H
#define TABFORM_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QMenu>
#include "video/videoplayer.h"
#include "utils/mtypes.h"

namespace Ui {
class TabForm;
}

class TabForm : public QWidget
{
    Q_OBJECT

public:
    explicit TabForm(QWidget *parent = nullptr);
    ~TabForm();

    VideoPlayer             *videoPlayer;


    //method
    void                    showFrame(cv::Mat mat);                 //显示画面到窗口
    void                    setZoomRatio();                         //设置画面放大比例
    void                    setVideoPos(int v=0);                   //设置视频的帧位置
    void                    video_goto(mtypes::VideoPos *pos);      //跳转视频到指定位置

private:
    Ui::TabForm                         *ui;                        // designer ui
    QGraphicsScene                      *scene;                     //场景
    QGraphicsPixmapItem                 *imgItem;                   //画面
    void                                initConnections();          //创建绝大部分信号连接
    mtypes::VideoPos                     _pos;                       //当前视频所在位置
    QMenu                               _frameMenu;                 //左下角的帧按钮显示菜单
    void                                _createFrameMenu();         //初始化左下角帧按钮显示菜单
    void                                _showCurrentPos();          //更新到当前视频位置
    void                                _setPosTime();              //设置位置时间


};

#endif // TABFORM_H
