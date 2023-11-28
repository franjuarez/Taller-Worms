/********************************************************************************
** Form generated from reading UI file 'joinwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.15
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JOINWINDOW_H
#define UI_JOINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_JoinWindow
{
public:
    QComboBox *availableMatchesComboBox;
    QPushButton *joinButton;
    QPushButton *refreshButton;

    void setupUi(QDialog *JoinWindow)
    {
        if (JoinWindow->objectName().isEmpty())
            JoinWindow->setObjectName(QString::fromUtf8("JoinWindow"));
        JoinWindow->resize(768, 703);
        JoinWindow->setStyleSheet(QString::fromUtf8("background-image: url(:/resources/images/Screenshot from 2023-11-11 10-46-54.png)"));
        availableMatchesComboBox = new QComboBox(JoinWindow);
        availableMatchesComboBox->setObjectName(QString::fromUtf8("availableMatchesComboBox"));
        availableMatchesComboBox->setGeometry(QRect(230, 620, 96, 19));
        joinButton = new QPushButton(JoinWindow);
        joinButton->setObjectName(QString::fromUtf8("joinButton"));
        joinButton->setGeometry(QRect(230, 650, 121, 29));
        QFont font;
        font.setFamily(QString::fromUtf8("Ubuntu Condensed"));
        font.setPointSize(17);
        font.setBold(true);
        font.setItalic(true);
        joinButton->setFont(font);
        joinButton->setStyleSheet(QString::fromUtf8("border-image: transparent;\n"
"background-color: rgb(211, 215, 207);\n"
"background-image: transparent;\n"
"\n"
"color: rgb(237, 212, 0);\n"
"\n"
""));
        refreshButton = new QPushButton(JoinWindow);
        refreshButton->setObjectName(QString::fromUtf8("refreshButton"));
        refreshButton->setGeometry(QRect(330, 620, 21, 21));
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("object-rotate-left");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        refreshButton->setIcon(icon);

        retranslateUi(JoinWindow);

        QMetaObject::connectSlotsByName(JoinWindow);
    } // setupUi

    void retranslateUi(QDialog *JoinWindow)
    {
        JoinWindow->setWindowTitle(QCoreApplication::translate("JoinWindow", "Dialog", nullptr));
        joinButton->setText(QCoreApplication::translate("JoinWindow", "join", nullptr));
        refreshButton->setStyleSheet(QCoreApplication::translate("JoinWindow", "border-image: transparent;\n"
"background-color: rgb(211, 215, 207);\n"
"background-image: url(:/resources/images/loshorroresdelaguerra.png);\n"
"color: rgb(237, 212, 0);\n"
"\n"
"", nullptr));
        refreshButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class JoinWindow: public Ui_JoinWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JOINWINDOW_H
