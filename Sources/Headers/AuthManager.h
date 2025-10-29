#pragma once

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QMutex>
#include <QUrl>

/**
 * @brief AuthManager
 * 单例类，负责管理 token 并发送带 Authorization 的网络请求
 * - token 仅存储于内存，不落盘
 * - 线程安全，通过 QMutex 保护 token
 */
class AuthManager : public QObject
{
    Q_OBJECT
public:
    // 获取单例
    static AuthManager& instance()
    {
        static AuthManager mgr;
        return mgr;
    }

    // 设置 token（线程安全）
    void setToken(const QString& t)
    {
        QMutexLocker locker(&mutex);
        token = t;
    }

    void setUsername(const QString& u){
        QMutexLocker locker(&mutex);
        username = u;
    }

    // 获取 token（线程安全）
    QString getToken() const
    {
        QMutexLocker locker(&mutex);
        return token;
    }

    QString getUsername() const{
        QMutexLocker locker(&mutex);
        return username;
    }

    /**
     * @brief get 发起 GET 请求
     * @param url 请求 URL
     * @return QNetworkReply* 异步返回
     */
    QNetworkReply* get(const QUrl& url)
    {
        QNetworkRequest req(url);
        {
            QMutexLocker locker(&mutex);
            if (!token.isEmpty())
                req.setRawHeader("Authorization", "Bearer " + token.toUtf8());
        }
        return networkManager.get(req);
    }

    /**
     * @brief post 发起 POST 请求
     * @param url 请求 URL
     * @param data 请求体（QByteArray，可是 JSON 数据）
     * @param contentType HTTP Content-Type，默认 application/json
     * @return QNetworkReply* 异步返回
     */
    QNetworkReply* post(const QUrl& url, const QByteArray& data, const QByteArray& contentType = "application/json")
    {
        QNetworkRequest req(url);
        req.setHeader(QNetworkRequest::ContentTypeHeader, contentType);
        {
            QMutexLocker locker(&mutex);
            if (!token.isEmpty())
                req.setRawHeader("Authorization", "Bearer " + token.toUtf8());
        }
        return networkManager.post(req, data);
    }

private:
    // 构造函数私有化，单例模式
    explicit AuthManager(QObject* parent = nullptr) : QObject(parent) {}

    // 禁止拷贝和赋值
    Q_DISABLE_COPY(AuthManager)

    mutable QMutex mutex;
    QString token;                      // 内存中保存的 token
    QString username;
    QNetworkAccessManager networkManager;  // 统一网络管理
};