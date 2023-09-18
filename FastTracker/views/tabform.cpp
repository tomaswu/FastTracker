#include "tabform.h"
#include "ui_tabform.h"

TabForm::TabForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabForm)
{
    ui->setupUi(this);
    videoPlayer = new TomasVideoReader;
}

TabForm::~TabForm()
{
    delete ui;
}
