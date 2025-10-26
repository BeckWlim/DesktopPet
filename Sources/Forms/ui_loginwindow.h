/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QTextEdit *edit_username;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_2;
    QTextEdit *edit_password;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *radio_save;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *button_submit;
    QPushButton *button_exit;

    void setupUi(QDialog *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName(QString::fromUtf8("LoginWindow"));
        LoginWindow->resize(333, 303);
        verticalLayout = new QVBoxLayout(LoginWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label = new QLabel(LoginWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(80, 40));

        horizontalLayout->addWidget(label);

        edit_username = new QTextEdit(LoginWindow);
        edit_username->setObjectName(QString::fromUtf8("edit_username"));
        edit_username->setMaximumSize(QSize(200, 40));

        horizontalLayout->addWidget(edit_username);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        label_2 = new QLabel(LoginWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMaximumSize(QSize(80, 40));

        horizontalLayout_2->addWidget(label_2);

        edit_password = new QTextEdit(LoginWindow);
        edit_password->setObjectName(QString::fromUtf8("edit_password"));
        edit_password->setMaximumSize(QSize(200, 40));

        horizontalLayout_2->addWidget(edit_password);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));

        verticalLayout->addLayout(horizontalLayout_4);

        radio_save = new QRadioButton(LoginWindow);
        radio_save->setObjectName(QString::fromUtf8("radio_save"));
        radio_save->setMinimumSize(QSize(0, 20));
        radio_save->setLayoutDirection(Qt::RightToLeft);

        verticalLayout->addWidget(radio_save);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        button_submit = new QPushButton(LoginWindow);
        button_submit->setObjectName(QString::fromUtf8("button_submit"));
        button_submit->setMaximumSize(QSize(100, 20));

        horizontalLayout_3->addWidget(button_submit);

        button_exit = new QPushButton(LoginWindow);
        button_exit->setObjectName(QString::fromUtf8("button_exit"));
        button_exit->setMaximumSize(QSize(100, 20));

        horizontalLayout_3->addWidget(button_exit);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QDialog *LoginWindow)
    {
        LoginWindow->setWindowTitle(QApplication::translate("LoginWindow", "Dialog", nullptr));
        label->setText(QApplication::translate("LoginWindow", "Username", nullptr));
        label_2->setText(QApplication::translate("LoginWindow", "Password", nullptr));
        radio_save->setText(QApplication::translate("LoginWindow", "Save username and password", nullptr));
        button_submit->setText(QApplication::translate("LoginWindow", "Submit", nullptr));
        button_exit->setText(QApplication::translate("LoginWindow", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
