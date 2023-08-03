//
// Created by 13191 on 2023/8/1.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "Headers/mainwindow.h"
#include "Forms/ui_mainwindow.h"
#include <QMouseEvent>
#include <QCursor>
#include <iostream>
#include <QBitmap>
#include <QPainter>
#include <QMovie>
#include <QTimer>

using namespace std;


MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWindow) {
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    this->setContextMenuPolicy(Qt::CustomContextMenu); // 设置菜单策略
    connect(this, &MainWindow::customContextMenuRequested, this, &MainWindow::_SlotPlayArgsMenu);
    setWindowIcon(QIcon(":/image/icon.png"));
    ui->setupUi(this);
    dialogWindow = new DialogWindow();
    catWindow = new CatWindow();
    // dialogWindow->show();
    //创建托盘
    QIcon icon = QIcon(":/image/icon.png");
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(icon);
    trayIcon->setToolTip("for lim"); //提示文字
    trayIcon->show();
    showAction = new QAction("温蒂", this);
    connect(showAction, &QAction::triggered, this, &MainWindow::show);
    quitAction = new QAction("退出", this);
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
    dialogAction = new QAction("对话", this);
    connect(dialogAction, &QAction::triggered, dialogWindow, &DialogWindow::show);
    kindergartenAction = new QAction("浣猫乐园", this);
    connect(kindergartenAction, &QAction::triggered, catWindow, &CatWindow::show);
    //创建托盘菜单
    trayMenu = new QMenu(this);
    trayMenu->addAction(showAction);
    trayMenu->addSeparator();
    trayMenu->addAction(kindergartenAction);
    trayMenu->addSeparator();
    trayMenu->addAction(dialogAction);
    trayMenu->addSeparator();
    trayMenu->addAction(quitAction);
    trayIcon->setContextMenu(trayMenu);
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    this->setAttribute(Qt::WA_TranslucentBackground);//设置窗体全透明
    movie = new QMovie(":/image/wendy_idle.gif");
    movie->setScaledSize(QSize(182, 201));
    movie->setSpeed(400);
    ui->label->setMovie(movie);
    movie->start();
    connect(movie, &QMovie::frameChanged, [=](int frameNumber){
        if(frameNumber == movie->frameCount()-1){
            movie->setFileName(QString(":/image/wendy_idle.gif"));
        }
    });
    actionTimer = new QTimer();
    actionTimer->setInterval(15000);
    actionTimer->setSingleShot(false);
    connect(actionTimer, &QTimer::timeout, this, [=](){
       movie->stop();
            // movie->setFileName(QString(":/image/wendy_dance.gif"));
       movie->start();
    });
    actionTimer->start();
    catWindow->show();
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason ireason)
{
    switch (ireason)
    {
        case QSystemTrayIcon::Trigger:
            this->showNormal();
            break;
        case QSystemTrayIcon::DoubleClick:
            this->showNormal();
            break;
        case QSystemTrayIcon::MiddleClick:
            break;
        default:
            break;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    this->windowPos = this->pos();       // 获得部件当前位置
    this->mousePos = event->globalPos(); // 获得鼠标位置
    this->dPos = mousePos - windowPos;   // 移动后部件所在的位置

    return QWidget::mousePressEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos() - this->dPos);
    return QWidget::mouseMoveEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    movie->stop();
    if(event->button() & Qt::LeftButton){
        this->movie->setFileName(QString(":/image/wendy_channel.gif"));
    }
    if(event->button() & Qt::RightButton){
        this->movie->setFileName(QString(":/image/wendy_channel_pst.gif"));
    }
    this->movie->start();
}

void MainWindow::_SlotPlayArgsMenu(const QPoint pos) {
    //创建菜单
    QMenu *pMenu = new QMenu(this);

    //隐藏
    QAction *pTest1 = new QAction("隐藏", this);
    connect(pTest1, &QAction::triggered, this, &MainWindow::hide);
    //添加一个图标
    QAction *pTest2 = new QAction("设置", this);
    QAction *pTest3 = new QAction("对话", this);

    //把QAction对象添加到菜单上
    pMenu->addAction(pTest1);
    pMenu->addSeparator();
    pMenu->addAction(pTest3);
    //添加分隔线
    pMenu->addSeparator();
    pMenu->addAction(pTest2);
    connect(pTest3, &QAction::triggered, dialogWindow, &DialogWindow::show);
    //在鼠标右键点击的地方显示菜单
    pMenu->exec(cursor().pos());
    //释放内存,若此处不手动释放，则必须等到程序结束时才都能释放
    QList<QAction*> list = pMenu->actions();
            foreach (QAction* pAction, list)
            delete pAction;
    delete pMenu;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(trayIcon->isVisible())
    {
        hide(); //隐藏窗口
        event->ignore(); //忽略事件
    }
}
void MainWindow::hideEvent(QHideEvent *event)
{
    if(trayIcon->isVisible())
    {
        hide(); //隐藏窗口
        event->ignore(); //忽略事件
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

