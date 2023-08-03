//
// Created by 13191 on 2023/8/3.
//

#ifndef DEMO_KITCOONWINDOW_H
#define DEMO_KITCOONWINDOW_H

#include <QWidget>
#include <QPropertyAnimation>
#include <iostream>
#include <vector>
#include "TaskCat.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class KitcoonWindow; }
QT_END_NAMESPACE

class KitcoonWindow : public QWidget {
Q_OBJECT

public:
    explicit KitcoonWindow(QWidget *parent = nullptr);
    ~KitcoonWindow() override;

    void taskDeal(TaskCat *task);
    QPoint positionModify(QPoint pos);

private:
    Ui::KitcoonWindow *ui;
    QMovie* cat;
    QPoint windowPos;
    QPoint mousePos;
    QPoint dPos;
    QPropertyAnimation* animation;
    QString direction;
    vector<TaskCat*> taskStack;
signals:
    void addTask();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private slots:
    void taskFinish();
    void createTaskThread();
};


#endif //DEMO_KITCOONWINDOW_H
