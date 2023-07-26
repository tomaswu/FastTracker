#include "historymanager.h"

HistoryManager::HistoryManager(QObject *parent)
    : QObject{parent}
{




}

HistoryManager::~HistoryManager(){



}


void HistoryManager::undo(){
    if(pos<0 || pos>=stepList.size())return;
    stepList[pos].backward();
    pos-=1;
}

void HistoryManager::redo(){
    if(stepList.size()==0 || pos+1>=stepList.size())return;
    pos+=1;
    stepList[pos].forward();
}

void HistoryManager::addNewStep(Step step){
    if(pos>0 && pos<stepList.size()){
        stepList = stepList.mid(0,pos+1);
    }
    stepList.append(step);
    pos+=1;
    if(stepList.size()>maxStep){
        stepList = stepList.mid(1,maxStep);
        pos-=1;
    }
}
