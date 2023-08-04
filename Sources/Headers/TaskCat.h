//
// Created by 13191 on 2023/8/3.
//

#ifndef DEMO_TASKCAT_H
#define DEMO_TASKCAT_H

#include <QWidget>

class TaskCat{
public:
    explicit TaskCat(QString task);
    TaskCat(QString task, QString pre, QString pst);
    QString task;
    QString pre;
    QString pst;
    QPoint pos;
    int intervalTime;
    void setInterval(int interval);
};


#endif //DEMO_TASKCAT_H
