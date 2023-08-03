//
// Created by 13191 on 2023/8/3.
//

// You may need to build the project (run Qt uic code generator) to get "ui_CatWindow.h" resolved

#include "catwindow.h"
#include "Forms/ui_catwindow.h"
#include "QMouseEvent"
#include <QMovie>
#include <QAction>
#include <QMenu>

CatWindow::CatWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::CatWindow) {
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    this->setContextMenuPolicy(Qt::CustomContextMenu); // 设置菜单策略
    connect(this, &CatWindow::customContextMenuRequested, this, &CatWindow::kindergartenSettings);
    this->setAttribute(Qt::WA_TranslucentBackground);//设置窗体全透明
    kindergarten = new QMovie(":/image/kitcoonden.gif");
    kindergarten->setSpeed(400);
    kindergarten->setScaledSize(QSize(333, 338));
    ui->label->setMovie(kindergarten);
    kindergarten->start();
    connect(kindergarten, &QMovie::frameChanged, [=](int frameNumber){
        if(frameNumber == kindergarten->frameCount()-1){
            kindergarten->setFileName(QString(":/image/kitcoonden.png"));
            kindergarten->start();
        }
    });
    cat = new KitcoonWindow(this);
}

void CatWindow::kindergartenSettings() {
    QMenu *pMenu = new QMenu(this);
    //隐藏
    QAction *hideAction = new QAction("hide", this);
    connect(hideAction, &QAction::triggered, this, &CatWindow::hide);
    //添加一个图标
    QAction *settingAction = new QAction("settings", this);

    //把QAction对象添加到菜单上
    pMenu->addAction(hideAction);
    pMenu->addSeparator();
    pMenu->addAction(settingAction);
    //在鼠标右键点击的地方显示菜单
    pMenu->exec(cursor().pos());
    //释放内存,若此处不手动释放，则必须等到程序结束时才都能释放
    QList<QAction*> list = pMenu->actions();
            foreach (QAction* pAction, list)
            delete pAction;
    delete pMenu;
}

void CatWindow::showEvent(QShowEvent *event) {
    // cout << this->x() << this->y() << endl;
    cat->move(cat->positionModify(this->pos()));
    cat->gartenPos = cat->positionModify(this->pos());
    cat->show();
}

void CatWindow::hideEvent(QHideEvent *event) {
    cat->hide();
}

void CatWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint pos = event->globalPos() - this->dPos;
    this->move(pos);
    cat->gartenPos = cat->positionModify(pos);
    return QWidget::mouseMoveEvent(event);
}

void CatWindow::mousePressEvent(QMouseEvent *event)
{
    this->tempPos = this->pos();
    this->windowPos = this->pos();       // 获得部件当前位置
    this->mousePos = event->globalPos(); // 获得鼠标位置
    this->dPos = mousePos - windowPos;   // 移动后部件所在的位置
    return QWidget::mousePressEvent(event);
}

void CatWindow::mouseReleaseEvent(QMouseEvent *event) {
    QPoint nowPos = this->pos();
    if(nowPos != tempPos && cat->mode == sleep){
        TaskCat* moveTask = new TaskCat(QString("move"));
        moveTask->pos = cat->positionModify(nowPos);
        this->cat->taskDeal(moveTask);
    }
}

CatWindow::~CatWindow() {
    delete ui;
}

