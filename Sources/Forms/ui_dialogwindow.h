/********************************************************************************
** Form generated from reading UI file 'dialogwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGWINDOW_H
#define UI_DIALOGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogWindow
{
public:
    QGridLayout *gridLayout;
    QListWidget *listWidget;
    QTextEdit *textEdit;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonSend;
    QPushButton *buttonClear;

    void setupUi(QWidget *DialogWindow)
    {
        if (DialogWindow->objectName().isEmpty())
            DialogWindow->setObjectName(QString::fromUtf8("DialogWindow"));
        DialogWindow->resize(358, 403);
        gridLayout = new QGridLayout(DialogWindow);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        listWidget = new QListWidget(DialogWindow);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        gridLayout->addWidget(listWidget, 0, 0, 1, 1);

        textEdit = new QTextEdit(DialogWindow);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        gridLayout->addWidget(textEdit, 1, 0, 1, 1);

        widget = new QWidget(DialogWindow);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonSend = new QPushButton(widget);
        buttonSend->setObjectName(QString::fromUtf8("buttonSend"));

        horizontalLayout->addWidget(buttonSend);

        buttonClear = new QPushButton(widget);
        buttonClear->setObjectName(QString::fromUtf8("buttonClear"));

        horizontalLayout->addWidget(buttonClear);


        gridLayout->addWidget(widget, 2, 0, 1, 1);

        gridLayout->setRowStretch(0, 4);
        gridLayout->setRowStretch(1, 1);
        gridLayout->setRowStretch(2, 1);

        retranslateUi(DialogWindow);

        QMetaObject::connectSlotsByName(DialogWindow);
    } // setupUi

    void retranslateUi(QWidget *DialogWindow)
    {
        DialogWindow->setWindowTitle(QApplication::translate("DialogWindow", "Dialog", nullptr));
        buttonSend->setText(QApplication::translate("DialogWindow", "send", nullptr));
        buttonClear->setText(QApplication::translate("DialogWindow", "clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogWindow: public Ui_DialogWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGWINDOW_H
