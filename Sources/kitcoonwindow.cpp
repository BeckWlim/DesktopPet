//
// Created by 13191 on 2023/8/3.
//

// You may need to build the project (run Qt uic code generator) to get "ui_KitcoonWindow.h" resolved

#include "kitcoonwindow.h"
#include "Forms/ui_kitcoonwindow.h"
#include <QMovie>
#include <QMouseEvent>
#include <cmath>
#include <iostream>

using namespace std;

KitcoonWindow::KitcoonWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::KitcoonWindow) {
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);//设置窗体全透明
    cat = new QMovie(":/image/cat_sleep.gif");
    cat->setSpeed(200);
    cat->setScaledSize(QSize(200, 150));
    ui->label->setMovie(cat);
    TaskCat* sleep = new TaskCat(QString("sleep"), QString("sleep_pre"), QString("sleep_pst"));
    taskDeal(sleep);
}

void KitcoonWindow::taskDeal(TaskCat* task) {
    if(this->taskStack.empty()){ // 栈空 直接载入任务
        this->taskStack.push_back(task);
        createTaskThread();
        return;
    }
    TaskCat* temp = taskStack.back(); // 得到栈顶任务
    if(temp->task == task->task){
        taskStack.pop_back();
    }
    cout << temp->task.toStdString() << endl;
    this->taskStack.push_back(task); // 载入需要执行的任务

    if(temp->pst != QString::null){ // 任务中断动画非空 载入中断动画
        this->taskStack.push_back(new TaskCat(temp->pst));
    }
    createTaskThread(); // 执行任务线程
}

void KitcoonWindow::taskFinish() {
    TaskCat* top = taskStack.back(); // 得到当前栈顶任务
    taskStack.pop_back(); // 弹出栈顶任务
    if(taskStack.empty()){ // 空栈 执行最近结束的任务
        taskStack.push_back(top);
        return;
    }
    TaskCat* temp = taskStack.back();
    if(temp->pre != QString::null && temp->pre != top->task){
        taskStack.push_back(new TaskCat(temp->pre));
    }
    createTaskThread();
}

void KitcoonWindow::createTaskThread() {
    TaskCat* task = taskStack.back();
    // cout << task.task.toStdString() << task.pre.toStdString() << task.pst.toStdString() << endl;
    if(task->task == "move"){
        animation = new QPropertyAnimation(this, "pos");
        QPoint currentPos = this->pos() - task->pos;
        double distance = sqrt(currentPos.x() * currentPos.x() + currentPos.y()*currentPos.y());
        double theta = asin(currentPos.y() / sqrt(currentPos.x()*currentPos.x() + currentPos.y()*currentPos.y()));
        if(abs(theta) > 0.7854 && currentPos.y()>0){
            this->direction = "up";
        }
        else if(abs(theta) > 0.7854){
            this->direction = "down";
        }
        else if(currentPos.x() > 0){
            this->direction = "left";
        }
        else{
            this->direction = "right";
        }
        animation->setDuration(distance * 10);
        animation->setStartValue(this->pos());
        animation->setEndValue(task->pos);
        this->cat->stop();
        QString actionStr = QString(":/image/cat_")+ this->direction+".gif";
        this->cat->setFileName(actionStr);
        this->cat->start();
        animation->start();
        connect(animation, &QPropertyAnimation::finished, this, &KitcoonWindow::taskFinish);
        cat->disconnect(this);
    }
    else{
        cat->stop();
        QString fileName = QString(":/image/cat_")+task->task+QString(".gif");
        cat->setFileName(fileName);
        cat->start();  // 载入任务动画
        connect(cat, &QMovie::frameChanged, this, [=](int frameNumber){
            if(frameNumber == cat->frameCount()-1){
                taskFinish();
            }
        }); // 动画播放完毕后进行任务终止操作
    }
}

QPoint KitcoonWindow::positionModify(QPoint pos) {
    QPoint pos_modify(pos.x()+120, pos.y()+30);
    return pos_modify;
}

void KitcoonWindow::mousePressEvent(QMouseEvent *event)
{
    this->windowPos = this->pos();       // 获得部件当前位置
    this->mousePos = event->globalPos(); // 获得鼠标位置
    this->dPos = mousePos - windowPos;   // 移动后部件所在的位置

    return QWidget::mousePressEvent(event);
}

void KitcoonWindow::mouseMoveEvent(QMouseEvent *event)
{
    // this->move(event->globalPos() - this->dPos);
    return QWidget::mouseMoveEvent(event);
}

KitcoonWindow::~KitcoonWindow() {
    delete ui;
}
