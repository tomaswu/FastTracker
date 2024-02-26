#ifndef DIALOGVIDEOGOTO_H
#define DIALOGVIDEOGOTO_H

#include <QDialog>
#include "utils/mtypes.h"

namespace Ui {
class DialogVideoGoto;
}

class DialogVideoGoto : public QDialog
{
    Q_OBJECT

public:
    explicit DialogVideoGoto(QWidget *parent = nullptr);
    ~DialogVideoGoto();

    void setFrame(int frame);
    void setTime(double t);
    void setStep(int step);

    int getGotoPara(mtypes::VideoPos *pos);

private:
    Ui::DialogVideoGoto *ui;
    mtypes::VideoPos    _pos;
};

#endif // DIALOGVIDEOGOTO_H
