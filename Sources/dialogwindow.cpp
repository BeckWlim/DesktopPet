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
#include <QtNetwork/QNetworkReply>
#include <QKeyEvent>
#include <QWebSocket>
#include <QUrlQuery>

#include "QNChatMessage.h"
#include "AuthManager.h"

DialogWindow::DialogWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::DialogWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/image/wendy.ico"));
    this->resize(600, 800);
    connect(ui->buttonSend, &QPushButton::clicked, this, &DialogWindow::buttonSendClicked);
    robotAPIManager = new QNetworkAccessManager();

    connect(this, &DialogWindow::robotReply, this, &DialogWindow::displayReply);
    ui->buttonSend->setFocus();
    ui->buttonSend->setDefault(true);
    ui->textEdit->installEventFilter(this);
    QFont font = QFont("Microsoft YaHei",12,2);
    ui->textEdit->setFont(font);
}

void DialogWindow::createWebSocket(){
    websocket = new QWebSocket();
    connect(websocket, &QWebSocket::connected, this, [=](){
        qDebug() << "[WebSocket] connected successfully";
    });
    connect(websocket, &QWebSocket::disconnected, this, [=](){
        qDebug() << "[WebSocket Disconnected]";
    });
    connect(websocket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this, [=](QAbstractSocket::SocketError error){
        qDebug() << "[WebSocket] Connection error:" << websocket->errorString();
    });

    connect(websocket, &QWebSocket::textMessageReceived, this, &DialogWindow::dealRobotMessage);

    QUrl url("ws://114.214.236.207:8081/ws/chat");
    QUrlQuery query;
    query.addQueryItem("username", AuthManager::instance().getUsername());
    url.setQuery(query);

    QNetworkRequest request(url);
    QString token = AuthManager::instance().getToken();
    if (!token.isEmpty()) {
        request.setRawHeader("Authorization", "Bearer " + token.toUtf8());
        qDebug() << "Websocket request";
    }

    qDebug() << "[WebSocket] Final URL:" << request.url().toString();
    for (const QByteArray &headerName : request.rawHeaderList()) {
        qDebug() << "[WebSocket] Header:" << headerName << "=" << request.rawHeader(headerName);
    }

    websocket->open(request);
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

void DialogWindow::chatRobot(const QString msg) {
    if (!websocket || websocket->state() != QAbstractSocket::ConnectedState) {
        qWarning() << "WebSocket not connected!";
        return;
    }
    websocket->sendTextMessage(msg);
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

void DialogWindow::dealRobotMessage(const QString& msg) {
    QJsonDocument doc = QJsonDocument::fromJson(msg.toUtf8());
    qDebug() << msg;
    if (!doc.isObject()) return;
    auto obj = doc.object();

    if (obj["type"].toString() == "session_init") {
        sessionId = obj["sessionId"].toString();
        qDebug() << "Session established with ID:" << sessionId;
    }else{
        if (obj.contains("answer")) {
            QJsonValue val = obj.value("answer");
            QString msg = val.toString();
            emit robotReply(msg);
        }
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



