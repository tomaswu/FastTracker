#ifndef TABFORM_H
#define TABFORM_H

#include <QWidget>
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


private:
    Ui::TabForm *ui;
};

#endif // TABFORM_H
