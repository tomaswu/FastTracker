#ifndef TABFORM_H
#define TABFORM_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include "video/videoplayer.h"

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


private:
    Ui::TabForm *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *imgItem;

    void initConnections();

};

#endif // TABFORM_H
