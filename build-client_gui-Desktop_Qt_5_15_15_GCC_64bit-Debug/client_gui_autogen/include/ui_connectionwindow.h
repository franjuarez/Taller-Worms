/********************************************************************************
** Form generated from reading UI file 'connectionwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.15
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTIONWINDOW_H
#define UI_CONNECTIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConnectionWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *portLineEdit;
    QLabel *label_3;
    QLabel *label_2;
    QLineEdit *addressLineEdit;
    QPushButton *pushButton;

    void setupUi(QMainWindow *ConnectionWindow)
    {
        if (ConnectionWindow->objectName().isEmpty())
            ConnectionWindow->setObjectName(QString::fromUtf8("ConnectionWindow"));
        ConnectionWindow->resize(703, 348);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ConnectionWindow->sizePolicy().hasHeightForWidth());
        ConnectionWindow->setSizePolicy(sizePolicy);
        ConnectionWindow->setAutoFillBackground(false);
        ConnectionWindow->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/loshorroresdelaguerra.png)  \n"
"0 0 0  strech strech;\n"
"\n"
""));
        centralwidget = new QWidget(ConnectionWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setAutoFillBackground(false);
        centralwidget->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
""));
        portLineEdit = new QLineEdit(centralwidget);
        portLineEdit->setObjectName(QString::fromUtf8("portLineEdit"));
        portLineEdit->setGeometry(QRect(116, 32, 125, 22));
        QFont font;
        font.setFamily(QString::fromUtf8("Ubuntu Condensed"));
        font.setPointSize(12);
        font.setBold(true);
        portLineEdit->setFont(font);
        portLineEdit->setAutoFillBackground(false);
        portLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);\n"
"color: rgb(237, 212, 0);\n"
"\n"
"border-image: rgb(85, 87, 83)"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 30, 80, 26));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Yrsa"));
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setItalic(true);
        label_3->setFont(font1);
        label_3->setAutoFillBackground(false);
        label_3->setStyleSheet(QString::fromUtf8("border-image: rgb(85, 87, 83);\n"
"color: rgb(237, 212, 0);\n"
"font: 700 italic 14pt \"Yrsa\";\n"
"\n"
""));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 62, 80, 26));
        label_2->setFont(font1);
        label_2->setAutoFillBackground(false);
        label_2->setStyleSheet(QString::fromUtf8("border-image: rgb(85, 87, 83);\n"
"color: rgb(237, 212, 0);\n"
"font: 700 italic 14pt \"Yrsa\";\n"
"\n"
""));
        addressLineEdit = new QLineEdit(centralwidget);
        addressLineEdit->setObjectName(QString::fromUtf8("addressLineEdit"));
        addressLineEdit->setGeometry(QRect(116, 64, 125, 22));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(addressLineEdit->sizePolicy().hasHeightForWidth());
        addressLineEdit->setSizePolicy(sizePolicy1);
        addressLineEdit->setFont(font);
        addressLineEdit->setAutoFillBackground(false);
        addressLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 52, 54);\n"
"color: rgb(237, 212, 0);\n"
"\n"
"border-image: rgb(85, 87, 83)"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(30, 104, 80, 23));
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(211, 215, 207);\n"
"border-image: transparent;\n"
""));
        ConnectionWindow->setCentralWidget(centralwidget);

        retranslateUi(ConnectionWindow);

        QMetaObject::connectSlotsByName(ConnectionWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ConnectionWindow)
    {
        ConnectionWindow->setWindowTitle(QCoreApplication::translate("ConnectionWindow", "ConnectionWindow", nullptr));
        portLineEdit->setPlaceholderText(QCoreApplication::translate("ConnectionWindow", "1234", nullptr));
        label_3->setText(QCoreApplication::translate("ConnectionWindow", "port", nullptr));
        label_2->setText(QCoreApplication::translate("ConnectionWindow", "address", nullptr));
        addressLineEdit->setPlaceholderText(QCoreApplication::translate("ConnectionWindow", "127.0.0.1", nullptr));
        pushButton->setText(QCoreApplication::translate("ConnectionWindow", "connect", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConnectionWindow: public Ui_ConnectionWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTIONWINDOW_H
