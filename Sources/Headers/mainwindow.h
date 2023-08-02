//
// Created by 13191 on 2023/8/1.
//

#ifndef DEMO_MAINWINDOW_H
#define DEMO_MAINWINDOW_H

#include <QWidget>
#include <QMenu>
#include <QSystemTrayIcon>
#include "dialogwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget {
Q_OBJECT

public:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    //记录鼠标，窗口位置
    QPoint windowPos;
    QPoint mousePos;
    QPoint dPos;
    QSystemTrayIcon *trayIcon;
    QAction* showAction, *quitAction, *dialogAction;
    QMenu* trayMenu;
    QMovie *movie;
    DialogWindow* dialogWindow;

private slots:
    void _SlotPlayArgsMenu(const QPoint pos);
    void closeEvent(QCloseEvent *event);
    void hideEvent(QHideEvent *event);
    void iconActivated(QSystemTrayIcon::ActivationReason ireason);
    void mouseReleaseEvent(QMouseEvent *event);
};


#endif //DEMO_MAINWINDOW_H
