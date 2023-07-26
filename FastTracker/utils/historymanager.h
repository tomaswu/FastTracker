#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <QObject>
#include <QList>


typedef void (*f_ptr)();

struct Step
{
    f_ptr forward{nullptr};
    f_ptr backward{nullptr};
};


class HistoryManager : public QObject
{
    Q_OBJECT
public:
    explicit HistoryManager(QObject *parent = nullptr);
    ~HistoryManager();

    //member
    int             maxStep{5};
    int             pos{-1};
    QList<Step>     stepList;


    //method
    void undo();
    void redo();
    void addNewStep(Step step);

signals:

};

#endif // HISTORYMANAGER_H
