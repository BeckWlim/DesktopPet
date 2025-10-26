#include "loginwindow.h"
#include "Forms/ui_loginwindow.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFile>
#include <QDialog>

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
        query.exec("CREATE TABLE IF NOT EXISTS user("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "username TEXT UNIQUE, "
                   "password TEXT)");
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

    QSqlDatabase db = QSqlDatabase::database("login_db");
    QSqlQuery query(db);

    // 检查账号密码是否存在

    if (true) {
        QMessageBox::information(this, "Success", "Login successful!");

        // 若勾选保存，则写入数据库（若不存在则插入）
        if (ui->radio_save->isChecked()) {
            QSqlQuery insertQuery(db);
            insertQuery.prepare("INSERT OR REPLACE INTO user (username, password) VALUES (:username, :password)");
            insertQuery.bindValue(":username", username);
            insertQuery.bindValue(":password", password);
            insertQuery.exec();
        }
        accept();
    } else {
        QMessageBox::critical(this, "Error", "Invalid username or password!");
    }
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
