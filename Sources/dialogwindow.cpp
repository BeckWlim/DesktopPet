//
// Created by 13191 on 2023/8/2.
//

// You may need to build the project (run Qt uic code generator) to get "ui_DialogWindow.h" resolved
#include "dialogwindow.h"
#include "Forms/ui_dialogwindow.h"
#include <QFontMetrics>
#include <QPaintEvent>
#include <QDateTime>
#include <QPainter>
#include <QMovie>
#include <QLabel>
#include <QDebug>
#include <QJsonParseError>
#include "QNChatMessage.h"
#include <QtNetwork/QNetworkReply>
#include <QKeyEvent>

DialogWindow::DialogWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::DialogWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/image/icon.png"));
    this->resize(600, 800);
    connect(ui->buttonSend, &QPushButton::clicked, this, &DialogWindow::buttonSendClicked);
    robotAPIManager = new QNetworkAccessManager();
    connect(robotAPIManager, &QNetworkAccessManager::finished, this, &DialogWindow::dealRobotMessage);
    connect(this, &DialogWindow::robotReply, this, &DialogWindow::displayReply);
    ui->buttonSend->setFocus();
    ui->buttonSend->setDefault(true);
    ui->textEdit->installEventFilter(this);
    QFont font = QFont("Microsoft YaHei",12,2);
    ui->textEdit->setFont(font);
}

void DialogWindow::setStyle(QString str) {
    QFile file(str);
    if(file.open(QFile::ReadOnly))
    {
        QTextStream filetext(&file);
        QString stylesheet = filetext.readAll();
        qApp->setStyleSheet(stylesheet);
        file.close();

    }
    else
    {
        qDebug()<<"Open  file fail "<<endl;
    }
}

void DialogWindow::chatRobot(QString msg) {
    QNetworkRequest request;
    request.setUrl(QUrl(QString("http://api.qingyunke.com/api.php?key=free&appid=0&msg=")+msg));
    robotAPIManager->get(request);
}

void DialogWindow::buttonSendClicked() {
    QString msg = ui->textEdit->toPlainText();
    ui->textEdit->setText("");
    QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //时间戳
    qDebug()<<"addMessage" << msg << time << ui->listWidget->count();
    dealMessageTime(time);
    QNChatMessage *messageW = new QNChatMessage(ui->listWidget->parentWidget());
    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
    dealMessage(messageW, item, msg, time, QNChatMessage::User_Me);
    ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
    chatRobot(msg);
}

void DialogWindow::dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time,  QNChatMessage::User_Type type)
{
    messageW->setFixedWidth(this->width());
    QSize size = messageW->fontRect(text);  // 定义字体大小
    item->setSizeHint(size);
    messageW->setText(text, time, size, type);
    ui->listWidget->setItemWidget(item, messageW);
}

void DialogWindow::dealRobotMessage(QNetworkReply *reply) {
    QByteArray array = reply->readAll();
    QJsonParseError error;
    QJsonDocument data = QJsonDocument::fromJson(array, &error);
    if (!data.isNull()) {
        QJsonObject obj = data.object();
        if (obj.contains("content")) {
            QJsonValue val = obj.value("content");
            QString msg = val.toString();
            emit robotReply(msg);
        }
        reply->deleteLater();
    }
}

void DialogWindow::displayReply(QString msg){
    QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //时间戳
    qDebug()<<"addMessage" << msg << time << ui->listWidget->count();
    dealMessageTime(time);
    QNChatMessage *messageW = new QNChatMessage(ui->listWidget->parentWidget());
    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
    dealMessage(messageW, item, msg, time, QNChatMessage::User_She);
    ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
}

void DialogWindow::dealMessageTime(QString curMsgTime)
{
    bool isShowTime = false;
    if(ui->listWidget->count() > 0) {
        QListWidgetItem* lastItem = ui->listWidget->item(ui->listWidget->count() - 1);
        QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(lastItem);
        int lastTime = messageW->time().toInt();
        int curTime = curMsgTime.toInt();
        qDebug() << "curTime lastTime:" << curTime - lastTime;  // 消息相差时间
        isShowTime = ((curTime - lastTime) > 60); // 两个消息相差一分钟
    } else {
        isShowTime = true;
    }
    if(isShowTime) {
        QNChatMessage* messageTime = new QNChatMessage(ui->listWidget->parentWidget());
        QListWidgetItem* itemTime = new QListWidgetItem(ui->listWidget);
        QSize size = QSize(this->width(), 40);
        messageTime->resize(size);
        itemTime->setSizeHint(size);
        messageTime->setText(curMsgTime, curMsgTime, size, QNChatMessage::User_Time);
        ui->listWidget->setItemWidget(itemTime, messageTime);
    }
}

void DialogWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    for(int i = 0; i < ui->listWidget->count(); i++) {
        QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(ui->listWidget->item(i));
        QListWidgetItem* item = ui->listWidget->item(i);
        dealMessage(messageW, item, messageW->text(), messageW->time(), messageW->userType());
    }
}


void DialogWindow::closeEvent(QCloseEvent *event)
{
    if(this->isVisible()){
        hide();
        event->ignore();
    }
}
void DialogWindow::hideEvent(QHideEvent *event)
{
    if(this->isVisible()){
        hide();
        event->ignore();
    }
}

DialogWindow::~DialogWindow() {
    delete ui;
}

bool DialogWindow::eventFilter(QObject *target, QEvent *event) {
    if(target == ui->textEdit)		//可替换
    {
        if(event->type() == QEvent::KeyPress)//回车键
        {
            QKeyEvent *k = static_cast<QKeyEvent *>(event);

            if(k->key() == Qt::Key_Return || k->key() == Qt::Key_Enter)
            {
                buttonSendClicked();		//替换为需要响应的函数事件，以这里的按钮为例
                return true;
            }
        }
    }
    return QWidget::eventFilter(target,event);
}



