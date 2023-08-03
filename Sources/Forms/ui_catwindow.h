/********************************************************************************
** Form generated from reading UI file 'catwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CATWINDOW_H
#define UI_CATWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CatWindow
{
public:
    QGridLayout *gridLayout;
    QLabel *label;

    void setupUi(QWidget *CatWindow)
    {
        if (CatWindow->objectName().isEmpty())
            CatWindow->setObjectName(QString::fromUtf8("CatWindow"));
        CatWindow->resize(300, 400);
        gridLayout = new QGridLayout(CatWindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(CatWindow);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);


        retranslateUi(CatWindow);

        QMetaObject::connectSlotsByName(CatWindow);
    } // setupUi

    void retranslateUi(QWidget *CatWindow)
    {
        CatWindow->setWindowTitle(QApplication::translate("CatWindow", "CatWindow", nullptr));
        label->setText(QApplication::translate("CatWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CatWindow: public Ui_CatWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CATWINDOW_H
