#include "views/tchartview.h"

#define qdb qDebug()

TChartView::TChartView(QWidget *parent):
    QChartView(parent)
{

}

void TChartView::mousePressEvent(QMouseEvent *event){
    if(actionFlag==0){
        if(event->button()==Qt::MouseButton::LeftButton){
            pressFlagL=true;
            originPos = event->pos();
            historyPos = originPos;
        }
        if(event->button()==Qt::MouseButton::RightButton){
            pressFlagR=true;
            originPos = event->pos();
            historyPos=originPos;
        }
    } // end if zoom

    if(actionFlag==1){
        if(event->button()==Qt::MouseButton::LeftButton){
            pressFlagL=true;
            originPos = event->pos();
            historyPos = originPos;
        }
    }//end if select
}

void TChartView::mouseReleaseEvent(QMouseEvent *event){

    if((actionFlag==1) && pressFlagL){
        auto rect = QRectF(originPos,event->pos());
        emit selectRectConfirm(rect);
    }

    pressFlagL=false;
    pressFlagR=false;
    event->accept();
}

void TChartView::mouseMoveEvent(QMouseEvent *event){
    emit posChange(event->pos());
    if((actionFlag==0) && pressFlagR){
        auto dx = event->pos().x()-historyPos.x();
        auto dy = event->pos().y()-historyPos.y();
        if(dx!=0 || dy!=0){
            emit zoomRange(dx,dy);
            historyPos = event->pos();
        }
    }
    if((actionFlag==0) && pressFlagL){
        auto dx = event->pos().x()-historyPos.x();
        auto dy = event->pos().y()-historyPos.y();
        if(dx!=0 || dy!=0){
            emit moveRange(dx,dy);
            historyPos = event->pos();
        }
    }

    if((actionFlag==1) && pressFlagL){
        auto rect = QRectF(originPos,event->pos());
        emit selectRect(rect);
    }

}



