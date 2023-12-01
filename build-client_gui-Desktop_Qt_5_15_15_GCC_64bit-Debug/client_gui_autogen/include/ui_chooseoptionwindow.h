/********************************************************************************
** Form generated from reading UI file 'chooseoptionwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.15
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSEOPTIONWINDOW_H
#define UI_CHOOSEOPTIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ChooseOptionWindow
{
public:
    QPushButton *joinButton_2;
    QPushButton *joinButton;
    QPushButton *createButton;
    QPushButton *createButton_2;

    void setupUi(QDialog *ChooseOptionWindow)
    {
        if (ChooseOptionWindow->objectName().isEmpty())
            ChooseOptionWindow->setObjectName(QString::fromUtf8("ChooseOptionWindow"));
        ChooseOptionWindow->resize(867, 434);
        ChooseOptionWindow->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/avioneta.png)  \n"
"0 0 0  strech strech;\n"
"\n"
""));
        joinButton_2 = new QPushButton(ChooseOptionWindow);
        joinButton_2->setObjectName(QString::fromUtf8("joinButton_2"));
        joinButton_2->setGeometry(QRect(0, 400, 158, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("Ubuntu Condensed"));
        font.setPointSize(20);
        font.setBold(true);
        font.setItalic(true);
        joinButton_2->setFont(font);
        joinButton_2->setAutoFillBackground(false);
        joinButton_2->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"background-image: transparent;\n"
"border-image: transparent;\n"
"  border: none;"));
        joinButton_2->setAutoDefault(true);
        joinButton = new QPushButton(ChooseOptionWindow);
        joinButton->setObjectName(QString::fromUtf8("joinButton"));
        joinButton->setGeometry(QRect(0, 326, 158, 31));
        joinButton->setFont(font);
        joinButton->setAutoFillBackground(false);
        joinButton->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"background-image: transparent;\n"
"border-image: transparent;\n"
"  border: none;"));
        joinButton->setAutoDefault(true);
        createButton = new QPushButton(ChooseOptionWindow);
        createButton->setObjectName(QString::fromUtf8("createButton"));
        createButton->setGeometry(QRect(0, 289, 158, 31));
        createButton->setFont(font);
        createButton->setAutoFillBackground(false);
        createButton->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: rgb(0, 0, 0);\n"
"border-color: rgb(0, 0, 0);\n"
"    border-width: 1px;\n"
"background-image: transparent;\n"
"border-image: transparent;\n"
"  border: none;"));
        createButton->setAutoDefault(true);
        createButton_2 = new QPushButton(ChooseOptionWindow);
        createButton_2->setObjectName(QString::fromUtf8("createButton_2"));
        createButton_2->setGeometry(QRect(0, 363, 158, 31));
        createButton_2->setFont(font);
        createButton_2->setAutoFillBackground(false);
        createButton_2->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: rgb(0, 0, 0);\n"
"border-color: rgb(0, 0, 0);\n"
"    border-width: 1px;\n"
"background-image: transparent;\n"
"border-image: transparent;\n"
"  border: none;"));
        createButton_2->setAutoDefault(true);

        retranslateUi(ChooseOptionWindow);

        QMetaObject::connectSlotsByName(ChooseOptionWindow);
    } // setupUi

    void retranslateUi(QDialog *ChooseOptionWindow)
    {
        ChooseOptionWindow->setWindowTitle(QCoreApplication::translate("ChooseOptionWindow", "Dialog", nullptr));
        joinButton_2->setText(QCoreApplication::translate("ChooseOptionWindow", "Quit", nullptr));
        joinButton->setText(QCoreApplication::translate("ChooseOptionWindow", "Join game", nullptr));
        createButton->setText(QCoreApplication::translate("ChooseOptionWindow", "Create game", nullptr));
        createButton_2->setText(QCoreApplication::translate("ChooseOptionWindow", "About", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChooseOptionWindow: public Ui_ChooseOptionWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSEOPTIONWINDOW_H
