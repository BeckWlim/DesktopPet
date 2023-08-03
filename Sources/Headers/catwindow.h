//
// Created by 13191 on 2023/8/3.
//

#ifndef DEMO_CATWINDOW_H
#define DEMO_CATWINDOW_H

#include <QWidget>
#include "kitcoonwindow.h"
#include <iostream>
#include <stack>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class CatWindow; }
QT_END_NAMESPACE

using namespace std;

class CatWindow : public QWidget {
Q_OBJECT

public:
    explicit CatWindow(QWidget *parent = nullptr);
    ~CatWindow() override;

private:
    Ui::CatWindow *ui;
    //记录鼠标，窗口位置
    QPoint windowPos;
    QPoint mousePos;
    QPoint dPos;
    QMovie* kindergarten;
    KitcoonWindow* cat;
    QPoint tempPos;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event);
    void showEvent(QShowEvent* event);
    void hideEvent(QHideEvent* event);

private slots:
    void kindergartenSettings();

};


#endif //DEMO_CATWINDOW_H
