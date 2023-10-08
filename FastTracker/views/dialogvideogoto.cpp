#include "dialogvideogoto.h"
#include "ui_dialogvideogoto.h"

DialogVideoGoto::DialogVideoGoto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogVideoGoto)
{
    ui->setupUi(this);
    connect(ui->spinBox_frame,&QSpinBox::valueChanged,this,&DialogVideoGoto::setFrame);
    connect(ui->doubleSpinBox_time,&QDoubleSpinBox::valueChanged,this,&DialogVideoGoto::setTime);
    connect(ui->spinBox_step,&QSpinBox::valueChanged,this,&DialogVideoGoto::setStep);
}

DialogVideoGoto::~DialogVideoGoto()
{
    delete ui;
}

void DialogVideoGoto::setFrame(int frame)
{
    _pos.setFrame(frame);

}

void DialogVideoGoto::setTime(double t)
{

}

void DialogVideoGoto::setStep(int step)
{

}

int DialogVideoGoto::getGotoPara(mtypes::VideoPos *pos)
{
    return 0;
}
