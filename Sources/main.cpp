#include <QApplication>
#include <QPushButton>
#include "mainwindow.h"
#include "loginwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow w;
    LoginWindow login;
    if (login.exec() == QDialog::Accepted) {
        MainWindow w;
        w.startShow();
        return app.exec();
    }
    return 0;
}
