#ifndef TABFORM_H
#define TABFORM_H

#include <QWidget>
#include "tomasvideoReader.h"

namespace Ui {
class TabForm;
}

class TabForm : public QWidget
{
    Q_OBJECT

public:
    explicit TabForm(QWidget *parent = nullptr);
    ~TabForm();

    TomasVideoReader            *videoPlayer;


private:
    Ui::TabForm *ui;
};

#endif // TABFORM_H
