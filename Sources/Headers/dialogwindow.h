//
// Created by 13191 on 2023/8/2.
//

#ifndef DEMO_DIALOGWINDOW_H
#define DEMO_DIALOGWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QListWidgetItem>
#include "QNChatMessage.h"
#include <QtNetwork/QNetworkAccessManager>


QT_BEGIN_NAMESPACE
namespace Ui { class DialogWindow; }
QT_END_NAMESPACE

class DialogWindow : public QWidget {
Q_OBJECT

public:
    explicit DialogWindow(QWidget *parent = nullptr);

    ~DialogWindow() override;
protected:
    void closeEvent(QCloseEvent *event);
    bool eventFilter(QObject *target, QEvent *event);
    void hideEvent(QHideEvent *event);
private:
    Ui::DialogWindow *ui;
    QNetworkAccessManager* robotAPIManager;
    void buttonSendClicked();
    void dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time,
                QNChatMessage::User_Type type);
    void dealRobotMessage(QNetworkReply *reply);
    void dealMessageTime(QString curMsgTime);
    void chatRobot(QString msg);
    void resizeEvent(QResizeEvent *event);
    void setStyle(QString str);
    signals:
    void robotReply(QString msg);

private slots:
    void displayReply(QString msg);

};


#endif //DEMO_DIALOGWINDOW_H
