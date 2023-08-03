/********************************************************************************
** Form generated from reading UI file 'kitcoonwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KITCOONWINDOW_H
#define UI_KITCOONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KitcoonWindow
{
public:
    QGridLayout *gridLayout;
    QLabel *label;

    void setupUi(QWidget *KitcoonWindow)
    {
        if (KitcoonWindow->objectName().isEmpty())
            KitcoonWindow->setObjectName(QString::fromUtf8("KitcoonWindow"));
        KitcoonWindow->resize(400, 300);
        gridLayout = new QGridLayout(KitcoonWindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(KitcoonWindow);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);


        retranslateUi(KitcoonWindow);

        QMetaObject::connectSlotsByName(KitcoonWindow);
    } // setupUi

    void retranslateUi(QWidget *KitcoonWindow)
    {
        KitcoonWindow->setWindowTitle(QApplication::translate("KitcoonWindow", "KitcoonWindow", nullptr));
        label->setText(QApplication::translate("KitcoonWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class KitcoonWindow: public Ui_KitcoonWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KITCOONWINDOW_H
