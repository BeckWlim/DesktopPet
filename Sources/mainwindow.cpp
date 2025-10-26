//
// Created by 13191 on 2023/8/1.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
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
    setWindowIcon(QIcon(":/image/cat.ico"));

    ui->setupUi(this);
    initWindow();
}

void MainWindow::initWindow(){
    static bool initialized = false;
    if(initialized) return;

    dialogWindow = new DialogWindow();
    catWindow = new CatWindow(this);
    // dialogWindow->show();
    //创建托盘
    QIcon icon = QIcon(":/image/cat.ico");
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(icon);
    trayIcon->setToolTip("for lim"); //提示文字

    quitAction = new QAction("退出", this);
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
    dialogAction = new QAction("对话", this);
    connect(dialogAction, &QAction::triggered, dialogWindow, &DialogWindow::show);
    kindergartenAction = new QAction("浣猫乐园", this);
    connect(kindergartenAction, &QAction::triggered, catWindow, &CatWindow::show);
    //创建托盘菜单
    trayMenu = new QMenu(this);
    trayMenu->addAction(kindergartenAction);
    trayMenu->addSeparator();
    trayMenu->addAction(dialogAction);
    trayMenu->addSeparator();
    trayMenu->addAction(quitAction);
    trayIcon->setContextMenu(trayMenu);
    connect(trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::iconActivated);
}

void MainWindow::startShow(){
    trayIcon->show();
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

