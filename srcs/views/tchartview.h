#ifndef TCHARTVIEW_H
#define TCHARTVIEW_H

#include <QObject>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QWidget>
#include <QMouseEvent>
#include <QRectF>

class TChartView:public QChartView
{
    Q_OBJECT
public:
    TChartView(QWidget *parent=nullptr);
    int actionFlag = 0; //外部控制 0为zoom 1为select
    bool pressFlagL = false;
    bool pressFlagR = false;
    QPoint historyPos;
    QPoint originPos;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

signals:
    void zoomRange(int dx,int dy);
    void moveRange(int dx,int dy);
    void posChange(QPointF pos);
    void selectRect(QRectF rect);
    void selectRectConfirm(QRectF rect);

};

#endif // TCHARTVIEW_H
