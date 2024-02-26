#ifndef TCHARTWINDOW_H
#define TCHARTWINDOW_H

#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QValueAxis>
#include <QtCharts/QLineSeries>
#include "tchartview.h"
#include <QRectF>

class TChartWindow:public QWidget
{
    Q_OBJECT
public:
    TChartWindow(QWidget *parent=nullptr);
    TChartView chartview;
    bool zoomFlag = false;
    bool selectFlag = false;

    QValueAxis ax,ay;
    QList<double> homeList={0,1,0,1};
    QList<double> historyList={0,1,0,1};

    QLineSeries line;
    QLineSeries linerect;
    QLineSeries lineExcept;
    QPoint historyPos;
    QPoint originPos;

    QPushButton btnHome,btnSelect,btnZoom,btnSave;
    QList<QPushButton*> btns;
    QHBoxLayout hbox;
    QVBoxLayout vbox;

    void saveFigure();
    void setSelectFlag();
    void setZoomFlag();
    void returnHome();
    void drawSelectRect(QRectF rect);
    void confirmRect(QRectF rect);

    void zoomRange(double dx,double dy);
    void moveRange(double dx,double dy);
    void setRange(double a,double b,double c,double d);
    void showPos(QPointF pos);
    void setTheme(QChart::ChartTheme theme);

    void autoRange();

    QLabel label;

};


#endif // TCHARTWINDOW_H
