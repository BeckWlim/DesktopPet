#include "loginwindow.h"
#include "Forms/ui_loginwindow.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFile>
#include <QDialog>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QUrl>
#include <QJsonDocument>

#include "AuthManager.h"

LoginWindow::LoginWindow(QDialog *parent)
    : QDialog(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    setWindowTitle("User Login");

    // 初始化数据库
    initDatabase();

    // 绑定按钮信号槽
    connect(ui->button_submit, &QPushButton::clicked, this, &LoginWindow::onSubmit);
    connect(ui->button_exit, &QPushButton::clicked, this, &LoginWindow::onExit);

    // 文本变化监听
    connect(ui->edit_username, &QTextEdit::textChanged, this, &LoginWindow::onTextChanged);
    connect(ui->edit_password, &QTextEdit::textChanged, this, &LoginWindow::onTextChanged);

    // 加载保存的账户信息
    loadSavedAccount();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

/**
 * 初始化 SQLite 数据库
 */
void LoginWindow::initDatabase()
{
    if (!QSqlDatabase::contains("login_db")) {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "login_db");
        db.setDatabaseName("login_data.db");
        if (!db.open()) {
            QMessageBox::critical(this, "Error", "Failed to open database: " + db.lastError().text());
            return;
        }

        QSqlQuery query(db);
        query.exec(
            "CREATE TABLE IF NOT EXISTS user("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "username TEXT UNIQUE, "
            "password TEXT)"
        );
    }
}

/**
 * 文本变化监听
 */
void LoginWindow::onTextChanged()
{
    QString username = ui->edit_username->toPlainText().trimmed();
    QString password = ui->edit_password->toPlainText().trimmed();

    // 简单示例：动态禁用提交按钮
    ui->button_submit->setEnabled(!username.isEmpty() && !password.isEmpty());
}

/**
 * 提交按钮槽函数
 */
void LoginWindow::onSubmit()
{
    QString username = ui->edit_username->toPlainText().trimmed();
    QString password = ui->edit_password->toPlainText().trimmed();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter username and password!");
        return;
    }

    QJsonObject json;
    json.insert("username", username);
    json.insert("password", password);
    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    QNetworkRequest request(QUrl("http://114.214.236.207:8081/api/auth/login"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkReply* reply = manager->post(request, data);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() != QNetworkReply::NoError) {
            QMessageBox::critical(this, "Error", reply->errorString());
            reply->deleteLater();
            manager->deleteLater();
            return;
        }

        QByteArray response = reply->readAll();
        qDebug() << "Response:" << response;

        QJsonDocument respDoc = QJsonDocument::fromJson(response);
        QJsonObject resp = respDoc.object();

        if (resp.contains("accessToken")) {
            QString token = resp["accessToken"].toString();
            AuthManager::instance().setToken(token);
            AuthManager::instance().setUsername(username);

            QMessageBox::information(this, "Success", "Login successful!");
            accept();
        } else {
            QMessageBox::critical(this, "Error", "Invalid username or password!");
        }

        reply->deleteLater();
        manager->deleteLater();
    });
}

/**
 * 退出按钮槽函数
 */
void LoginWindow::onExit()
{
    QApplication::quit();
}

/**
 * 从数据库加载已保存账号
 */
void LoginWindow::loadSavedAccount()
{
    QSqlDatabase db = QSqlDatabase::database("login_db");
    QSqlQuery query(db);
    query.exec("SELECT username, password FROM user ORDER BY id DESC LIMIT 1");
    if (query.next()) {
        ui->edit_username->setText(query.value(0).toString());
        ui->edit_password->setText(query.value(1).toString());
        ui->radio_save->setChecked(true);
    }
}
