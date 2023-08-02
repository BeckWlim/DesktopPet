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

using namespace std;


MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWindow) {
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &MainWindow::customContextMenuRequested, this, &MainWindow::_SlotPlayArgsMenu);
    // setWindowOpacity(0.7); //设置窗体透明度
    setWindowIcon(QIcon(":/image/icon.png"));
    ui->setupUi(this);
    dialogWindow = new DialogWindow();
    // dialogWindow->show();
    //创建托盘
    QIcon icon = QIcon(":/image/icon.png");
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(icon);
    trayIcon->setToolTip("for lim"); //提示文字
    trayIcon->show();
    showAction = new QAction("show", this);
    connect(showAction, &QAction::triggered, this, &MainWindow::show);
    quitAction = new QAction("exit", this);
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
    dialogAction = new QAction("dialog", this);
    connect(dialogAction, &QAction::triggered, dialogWindow, &DialogWindow::show);
    //创建托盘菜单
    trayMenu = new QMenu(this);
    trayMenu->addAction(showAction);
    trayMenu->addSeparator();
    trayMenu->addAction(quitAction);
    trayMenu->addSeparator();
    trayMenu->addAction(dialogAction);
    trayIcon->setContextMenu(trayMenu);
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    /*
    QPixmap mask(":/image/petMain.png");
    setMask(QBitmap(mask.mask()));
    QPalette p;
    p.setBrush(QPalette::Window,QBrush(mask));
    setPalette(p);
    */
    this->setAttribute(Qt::WA_TranslucentBackground);//设置窗体全透明
    movie = new QMovie(":/image/wendyIdol.png");
    movie->setSpeed(300);
    ui->label->setMovie(movie);
    movie->start();
    connect(movie, &QMovie::frameChanged, [=](int frameNumber){
        if(frameNumber == movie->frameCount()-1){
            movie->setFileName(QString(":/image/wendyIdol.png"));
        }
    });
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
    this->movie->setFileName(QString(":/image/wendy.gif"));
    this->movie->start();
}

void MainWindow::_SlotPlayArgsMenu(const QPoint pos) {
    //创建菜单
    QMenu *pMenu = new QMenu(this);

    //隐藏
    QAction *pTest1 = new QAction("hide", this);
    connect(pTest1, &QAction::triggered, this, &MainWindow::hide);
    //添加一个图标
    QAction *pTest2 = new QAction("settings", this);
    QAction *pTest3 = new QAction("dialog", this);

    //把QAction对象添加到菜单上
    pMenu->addAction(pTest1);
    pMenu->addSeparator();
    pMenu->addAction(pTest2);
    //添加分隔线
    pMenu->addSeparator();
    pMenu->addAction(pTest3);
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

