#include "views/tchartwindow.h"

#include <QSizePolicy>

#define qdb qDebug()

TChartWindow::TChartWindow(QWidget *parent):
    QWidget(parent)
{
    btns.append(&btnHome);
    btns.append(&btnSelect);
    btns.append(&btnZoom);
    btns.append(&btnSave);

    btnHome.setIcon(QIcon(":/image/ico/home.png"));
    btnZoom.setIcon(QIcon(":/image/ico/move.png"));
    btnSelect.setIcon(QIcon(":/image/ico/zoom.png"));
    btnSave.setIcon(QIcon(":/image/ico/save2.png"));

    connect(&btnHome,&QPushButton::clicked,this,&TChartWindow::returnHome);
    connect(&btnSave,&QPushButton::clicked,this,&TChartWindow::saveFigure);
    connect(&btnSelect,&QPushButton::clicked,this,&TChartWindow::setSelectFlag);
    connect(&btnZoom,&QPushButton::clicked,this,&TChartWindow::setZoomFlag);
    connect(&chartview,&TChartView::posChange,this,&TChartWindow::showPos);
    connect(&chartview,&TChartView::zoomRange,this,&TChartWindow::zoomRange);
    connect(&chartview,&TChartView::moveRange,this,&TChartWindow::moveRange);
    connect(&chartview,&TChartView::selectRect,this,&TChartWindow::drawSelectRect);
    connect(&chartview,&TChartView::selectRectConfirm,this,&TChartWindow::confirmRect);

    for(int i=0;i<4;i++){
        btns[i]->setMinimumHeight(26);
        btns[i]->setMinimumWidth(26);
        hbox.addWidget(btns[i]);
        if(i>0 && i<3){
            btns[i]->setCheckable(true);
        }
    }

    chartview.chart()->addAxis(&ax,Qt::AlignBottom);
    chartview.chart()->addAxis(&ay,Qt::AlignLeft);
    chartview.chart()->addSeries(&line);
    line.attachAxis(&ax);
    line.attachAxis(&ay);

    chartview.chart()->addSeries(&linerect);
    linerect.attachAxis(&ax);
    linerect.attachAxis(&ay);

    chartview.chart()->addSeries(&lineExcept);
    lineExcept.attachAxis(&ax);
    lineExcept.attachAxis(&ay);

    hbox.addStretch();
    hbox.addWidget(&label);
    vbox.addLayout(&hbox);
    vbox.addWidget(&chartview);
    this->setLayout(&vbox);

    auto pen = QPen(Qt::lightGray,1,Qt::DotLine);
    linerect.setPen(pen);
    auto pen2 = QPen(Qt::red,1,Qt::DashLine);
    lineExcept.setPen(pen2);

    chartview.setRenderHint(QPainter::RenderHint::Antialiasing);

    ay.setTitleText("Voltge(V)");
    ax.setTitleText("Time(s)");
}

void TChartWindow::saveFigure(){

    auto pic = chartview.grab();
    auto filename = QFileDialog::getSaveFileName(this,"save Fig","./","*.png");
    if(filename=="")return;
    pic.save(filename);

}

void TChartWindow::returnHome(){
    setRange(homeList[0],homeList[1],homeList[2],homeList[3]);
}

void TChartWindow::setSelectFlag(){
    selectFlag=btnSelect.isChecked();
    if(selectFlag){
        btnZoom.setChecked(false);
        zoomFlag=false;
        chartview.actionFlag=1;
    }
}

void TChartWindow::setZoomFlag(){
    zoomFlag=btnZoom.isChecked();
    if(zoomFlag){
        btnSelect.setChecked(false);
        selectFlag=false;
        chartview.actionFlag=0;
    }
}

void TChartWindow::zoomRange(double dx,double dy){
    if(zoomFlag){
        auto xr = ax.max()-ax.min();
        auto yr = ay.max()-ay.min();
        int krx = dx==0? 0 : dx/abs(dx);
        int kry = dy==0? 0 : dy/abs(dy);
        double rvelocity=0.01;
        historyList[0]=historyList[0]+xr*rvelocity*krx;
        historyList[1] = historyList[1]-xr*rvelocity*krx;
        historyList[2] = historyList[2]-yr*rvelocity*kry;
        historyList[3] = historyList[3]+yr*rvelocity*kry;
        ax.setRange(historyList[0],historyList[1]);
        ay.setRange(historyList[2],historyList[3]);
    }

}

void TChartWindow::moveRange(double dx,double dy){
    if(zoomFlag){
        auto ca = chartview.chart()->plotArea();
        auto cw = ca.width();
        auto ch = ca.height();

        auto xr = historyList[1]-historyList[0];
        auto yr = historyList[3]-historyList[2];

        historyList[0] = historyList[0]-xr*dx/cw;
        historyList[1] = historyList[1]-xr*dx/cw;

        historyList[2] = historyList[2]+yr*dy/ch;
        historyList[3] = historyList[3]+yr*dy/ch;

        ax.setRange(historyList[0],historyList[1]);
        ay.setRange(historyList[2],historyList[3]);
    }
}

void TChartWindow::showPos(QPointF pos){

    auto ca = chartview.chart()->plotArea();
    auto cw = ca.width();
    auto ch = ca.height();

    auto xr = ax.max()-ax.min();
    auto yr = ay.max()-ay.min();

    auto xlabel = ax.min()+(pos.x()-ca.x())/cw*xr;
    auto ylable = ay.max()-(pos.y()-ca.y())/ch*yr;
    QString s = QString("x:%1,y:%2").arg(xlabel).arg(ylable);
    label.setText(s);
}

void TChartWindow::autoRange(){
    int n = line.count();
    if(n<2)return;
    double minx=line.at(0).x();
    double maxx=minx;
    double miny=line.at(0).y();
    double maxy=miny;
    for(int i=1;i<n;i++){
        auto x = line.at(i).x();
        auto y = line.at(i).y();
        minx = minx<x? minx:x;
        maxx = maxx>x? maxx:x;
        miny = miny<y? miny:y;
        maxy = maxy>y? maxy:y;
    }

    if(lineExcept.count()>0){
        miny = miny < lineExcept.at(0).y()? miny:lineExcept.at(0).y();
        maxy = maxy > lineExcept.at(0).y()? maxy:lineExcept.at(0).y();
    }

    if(maxx==minx){
        maxx=maxx+1;
        minx=minx-1;
    }else{
        auto d=maxx-minx;
        maxx+=d*0.1;
        minx-=d*0.1;
    }

    if(maxy==miny){
        maxy+=1;
        miny-=1;
    }else{
        auto d = maxy-miny;
        miny-=d*0.1;
        maxy+=d*0.1;
    }

    homeList[0]=minx;
    homeList[1]=maxx;
    homeList[2]=miny;
    homeList[3]=maxy;
    setRange(minx,maxx,miny,maxy);

}

void TChartWindow::drawSelectRect(QRectF rect){
    QList<QPointF> s;
    auto ca = chartview.chart()->plotArea();
    auto cw = ca.width();
    auto ch = ca.height();

    auto xr = ax.max()-ax.min();
    auto yr = ay.max()-ay.min();
    auto x=ax.min()+(rect.x()-ca.x())/cw*xr;
    auto y=ay.max()-(rect.y()-ca.y())/ch*yr;
    auto w=rect.width()/cw*xr;
    auto h=rect.height()/ch*yr;

    s.push_back(QPointF(x,y));
    s.push_back(QPointF(x+w,y));
    s.push_back(QPointF(x+w,y-h));
    s.push_back(QPointF(x,y-h));
    s.push_back(QPointF(x,y));
    linerect.replace(s);
    chartview.update();
}

void TChartWindow::confirmRect(QRectF rect){
    linerect.clear();
    auto ca = chartview.chart()->plotArea();
    auto cw = ca.width();
    auto ch = ca.height();

    auto xr = ax.max()-ax.min();
    auto yr = ay.max()-ay.min();
    auto x=ax.min()+(rect.x()-ca.x())/cw*xr;
    auto y=ay.max()-(rect.y()-ca.y())/ch*yr;
    auto w=rect.width()/cw*xr;
    auto h=rect.height()/ch*yr;

    double a,b,c,d;
    a=x<=x+w? x:x+w;
    b=x>=x+w? x:x+w;
    c=y<=y-h? y:y-h;
    d=y>=y-h? y:y-h;

    setRange(a,b,c,d);
}

void TChartWindow::setRange(double a,double b,double c,double d){
    historyList[0]=a;
    historyList[1]=b;
    historyList[2]=c;
    historyList[3]=d;
    ax.setRange(a,b);
    ay.setRange(c,d);
}

void TChartWindow::setTheme(QChart::ChartTheme theme){
    chartview.chart()->setTheme(theme);
    auto pen = QPen(Qt::gray,1,Qt::DotLine);
    linerect.setPen(pen);
    auto pen2 = QPen(Qt::red,1,Qt::DashLine);
    lineExcept.setPen(pen2);
}



