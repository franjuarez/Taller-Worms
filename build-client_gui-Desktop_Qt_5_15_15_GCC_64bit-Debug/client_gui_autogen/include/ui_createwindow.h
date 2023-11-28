/********************************************************************************
** Form generated from reading UI file 'createwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.15
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEWINDOW_H
#define UI_CREATEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CreateWindow
{
public:
    QPushButton *smallButton;
    QPushButton *subsueloButton;
    QPushButton *mediumButton;
    QPushButton *dedustButton;
    QPushButton *testButton;
    QLabel *label;

    void setupUi(QDialog *CreateWindow)
    {
        if (CreateWindow->objectName().isEmpty())
            CreateWindow->setObjectName(QString::fromUtf8("CreateWindow"));
        CreateWindow->resize(834, 350);
        QFont font;
        font.setFamily(QString::fromUtf8("DejaVu Serif"));
        font.setPointSize(20);
        font.setBold(true);
        font.setItalic(true);
        CreateWindow->setFont(font);
        CreateWindow->setAutoFillBackground(false);
        CreateWindow->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/pantano.png)\n"
""));
        smallButton = new QPushButton(CreateWindow);
        smallButton->setObjectName(QString::fromUtf8("smallButton"));
        smallButton->setGeometry(QRect(36, 190, 145, 129));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(smallButton->sizePolicy().hasHeightForWidth());
        smallButton->setSizePolicy(sizePolicy);
        smallButton->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/previews/small_preview.png) stretch stretch\n"
""));
        subsueloButton = new QPushButton(CreateWindow);
        subsueloButton->setObjectName(QString::fromUtf8("subsueloButton"));
        subsueloButton->setGeometry(QRect(640, 190, 145, 129));
        sizePolicy.setHeightForWidth(subsueloButton->sizePolicy().hasHeightForWidth());
        subsueloButton->setSizePolicy(sizePolicy);
        subsueloButton->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/previews/subsuelo_preview.png)"));
        mediumButton = new QPushButton(CreateWindow);
        mediumButton->setObjectName(QString::fromUtf8("mediumButton"));
        mediumButton->setGeometry(QRect(338, 190, 145, 129));
        sizePolicy.setHeightForWidth(mediumButton->sizePolicy().hasHeightForWidth());
        mediumButton->setSizePolicy(sizePolicy);
        mediumButton->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/previews/medium_preview.png)"));
        dedustButton = new QPushButton(CreateWindow);
        dedustButton->setObjectName(QString::fromUtf8("dedustButton"));
        dedustButton->setGeometry(QRect(489, 190, 145, 129));
        sizePolicy.setHeightForWidth(dedustButton->sizePolicy().hasHeightForWidth());
        dedustButton->setSizePolicy(sizePolicy);
        dedustButton->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/previews/dust2_preview.png)"));
        testButton = new QPushButton(CreateWindow);
        testButton->setObjectName(QString::fromUtf8("testButton"));
        testButton->setGeometry(QRect(187, 190, 145, 129));
        sizePolicy.setHeightForWidth(testButton->sizePolicy().hasHeightForWidth());
        testButton->setSizePolicy(sizePolicy);
        testButton->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/previews/test_preview.png)"));
        label = new QLabel(CreateWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 181, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("DejaVu Serif"));
        font1.setPointSize(17);
        font1.setBold(true);
        font1.setItalic(true);
        label->setFont(font1);
        label->setAutoFillBackground(false);
        label->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border-color: rgb(46, 52, 54);\n"
"border-image: transparent;\n"
"background-image: transparent;"));

        retranslateUi(CreateWindow);

        QMetaObject::connectSlotsByName(CreateWindow);
    } // setupUi

    void retranslateUi(QDialog *CreateWindow)
    {
        CreateWindow->setWindowTitle(QCoreApplication::translate("CreateWindow", "Dialog", nullptr));
        smallButton->setText(QString());
        subsueloButton->setText(QString());
        mediumButton->setText(QString());
        dedustButton->setText(QString());
        testButton->setText(QString());
        label->setText(QCoreApplication::translate("CreateWindow", "Choose Map:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateWindow: public Ui_CreateWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEWINDOW_H
