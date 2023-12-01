/********************************************************************************
** Form generated from reading UI file 'aboutwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.15
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTWINDOW_H
#define UI_ABOUTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_AboutWindow
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;

    void setupUi(QDialog *AboutWindow)
    {
        if (AboutWindow->objectName().isEmpty())
            AboutWindow->setObjectName(QString::fromUtf8("AboutWindow"));
        AboutWindow->resize(928, 606);
        label = new QLabel(AboutWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(130, 10, 711, 491));
        label->setPixmap(QPixmap(QString::fromUtf8(":/resources/images/literalmentenosotros.jpg")));
        label_2 = new QLabel(AboutWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(210, 510, 101, 31));
        label_2->setStyleSheet(QString::fromUtf8("font: 700 10pt \"Umpush\";"));
        label_3 = new QLabel(AboutWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(630, 510, 161, 41));
        label_3->setStyleSheet(QString::fromUtf8("font: 700 10pt \"Umpush\";"));
        label_4 = new QLabel(AboutWindow);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(430, 510, 101, 31));
        label_4->setStyleSheet(QString::fromUtf8("font: 700 10pt \"Umpush\";"));
        label_5 = new QLabel(AboutWindow);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(330, 560, 271, 16));

        retranslateUi(AboutWindow);

        QMetaObject::connectSlotsByName(AboutWindow);
    } // setupUi

    void retranslateUi(QDialog *AboutWindow)
    {
        AboutWindow->setWindowTitle(QCoreApplication::translate("AboutWindow", "Dialog", nullptr));
        label->setText(QString());
        label_2->setText(QCoreApplication::translate("AboutWindow", "Joaco pandolfi", nullptr));
        label_3->setText(QCoreApplication::translate("AboutWindow", "Monke (francisco juarez)", nullptr));
        label_4->setText(QCoreApplication::translate("AboutWindow", "Martu Lozano", nullptr));
        label_5->setText(QCoreApplication::translate("AboutWindow", "https://github.com/franjuarez/Taller-Worms", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AboutWindow: public Ui_AboutWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTWINDOW_H
