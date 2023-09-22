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
    void                    showFrame(cv::Mat mat);
    void                    setZoomRatio();
    void                    setMaxFrameValue(int value);
    void                    setVideoPos(int v=0);

    void                    video_goto();

private:
    Ui::TabForm                         *ui;
    QGraphicsScene                      *scene;
    QGraphicsPixmapItem                 *imgItem;
    void                                initConnections();

    VideoPos                            _pos;
    QMenu                               _frameMenu; //左下角的帧按钮显示菜单
    void                                _createFrameMenu(); //初始化左下角帧按钮显示菜单




};

#endif // TABFORM_H
