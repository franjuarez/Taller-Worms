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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CreateWindow
{
public:
    QLabel *label;
    QPushButton *dedustButton;
    QPushButton *mediumButton;
    QPushButton *subsueloButton;
    QPushButton *smallButton;
    QPushButton *testButton;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QSpinBox *amtOfPlayersSpinBox;
    QLineEdit *matchNameTextEdit;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QLabel *label_2;

    void setupUi(QDialog *CreateWindow)
    {
        if (CreateWindow->objectName().isEmpty())
            CreateWindow->setObjectName(QString::fromUtf8("CreateWindow"));
        CreateWindow->resize(952, 594);
        QFont font;
        font.setFamily(QString::fromUtf8("DejaVu Serif"));
        font.setPointSize(20);
        font.setBold(true);
        font.setItalic(true);
        CreateWindow->setFont(font);
        CreateWindow->setAutoFillBackground(false);
        CreateWindow->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/pantano.png)\n"
""));
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
        dedustButton = new QPushButton(CreateWindow);
        dedustButton->setObjectName(QString::fromUtf8("dedustButton"));
        dedustButton->setGeometry(QRect(40, 330, 165, 179));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dedustButton->sizePolicy().hasHeightForWidth());
        dedustButton->setSizePolicy(sizePolicy);
        dedustButton->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/previews/dust2_preview.png)"));
        mediumButton = new QPushButton(CreateWindow);
        mediumButton->setObjectName(QString::fromUtf8("mediumButton"));
        mediumButton->setGeometry(QRect(553, 330, 165, 179));
        sizePolicy.setHeightForWidth(mediumButton->sizePolicy().hasHeightForWidth());
        mediumButton->setSizePolicy(sizePolicy);
        mediumButton->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/previews/medium_preview.png)"));
        subsueloButton = new QPushButton(CreateWindow);
        subsueloButton->setObjectName(QString::fromUtf8("subsueloButton"));
        subsueloButton->setGeometry(QRect(724, 330, 165, 179));
        sizePolicy.setHeightForWidth(subsueloButton->sizePolicy().hasHeightForWidth());
        subsueloButton->setSizePolicy(sizePolicy);
        subsueloButton->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/previews/subsuelo_preview.png)"));
        smallButton = new QPushButton(CreateWindow);
        smallButton->setObjectName(QString::fromUtf8("smallButton"));
        smallButton->setGeometry(QRect(382, 330, 165, 179));
        sizePolicy.setHeightForWidth(smallButton->sizePolicy().hasHeightForWidth());
        smallButton->setSizePolicy(sizePolicy);
        smallButton->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/previews/small_preview.png) stretch stretch\n"
""));
        testButton = new QPushButton(CreateWindow);
        testButton->setObjectName(QString::fromUtf8("testButton"));
        testButton->setGeometry(QRect(211, 330, 165, 179));
        sizePolicy.setHeightForWidth(testButton->sizePolicy().hasHeightForWidth());
        testButton->setSizePolicy(sizePolicy);
        testButton->setStyleSheet(QString::fromUtf8("border-image: url(:/resources/images/previews/test_preview.png)"));
        verticalLayoutWidget = new QWidget(CreateWindow);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(30, 120, 221, 91));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        amtOfPlayersSpinBox = new QSpinBox(verticalLayoutWidget);
        amtOfPlayersSpinBox->setObjectName(QString::fromUtf8("amtOfPlayersSpinBox"));
        amtOfPlayersSpinBox->setStyleSheet(QString::fromUtf8("border-image: transparent;\n"
"background-image: transparent;\n"
"background-color: rgb(211, 215, 207)\n"
""));
        amtOfPlayersSpinBox->setMinimum(1);
        amtOfPlayersSpinBox->setMaximum(4);

        verticalLayout->addWidget(amtOfPlayersSpinBox);

        matchNameTextEdit = new QLineEdit(verticalLayoutWidget);
        matchNameTextEdit->setObjectName(QString::fromUtf8("matchNameTextEdit"));
        matchNameTextEdit->setStyleSheet(QString::fromUtf8("border-image: transparent;\n"
"background-image: transparent;\n"
"background-color: rgb(211, 215, 207)\n"
""));

        verticalLayout->addWidget(matchNameTextEdit);

        comboBox = new QComboBox(CreateWindow);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(40, 540, 161, 23));
        comboBox->setStyleSheet(QString::fromUtf8("border-image: transparent;\n"
"background-image: transparent;\n"
"background-color: rgb(211, 215, 207)\n"
""));
        pushButton = new QPushButton(CreateWindow);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(210, 540, 131, 23));
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(211, 215, 207);\n"
"border-image: transparent;\n"
""));
        label_2 = new QLabel(CreateWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 280, 181, 41));
        label_2->setFont(font1);
        label_2->setAutoFillBackground(false);
        label_2->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border-color: rgb(46, 52, 54);\n"
"color:  rgb(255,255,255);\n"
"border-image: transparent;\n"
"background-image: transparent;"));

        retranslateUi(CreateWindow);

        QMetaObject::connectSlotsByName(CreateWindow);
    } // setupUi

    void retranslateUi(QDialog *CreateWindow)
    {
        CreateWindow->setWindowTitle(QCoreApplication::translate("CreateWindow", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("CreateWindow", "Choose Map:", nullptr));
        dedustButton->setText(QString());
        mediumButton->setText(QString());
        subsueloButton->setText(QString());
        smallButton->setText(QString());
        testButton->setText(QString());
        matchNameTextEdit->setPlaceholderText(QCoreApplication::translate("CreateWindow", "match name", nullptr));
        comboBox->setPlaceholderText(QCoreApplication::translate("CreateWindow", "custom map", nullptr));
        pushButton->setText(QCoreApplication::translate("CreateWindow", "choose custom map", nullptr));
        label_2->setText(QCoreApplication::translate("CreateWindow", "Official Maps:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateWindow: public Ui_CreateWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEWINDOW_H
