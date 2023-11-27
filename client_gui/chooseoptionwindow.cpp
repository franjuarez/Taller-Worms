#include "chooseoptionwindow.h"
#include "ui_chooseoptionwindow.h"

ChooseOptionWindow::ChooseOptionWindow(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::ChooseOptionWindow)
{
    ui->setupUi(this);
    this->joinWindow = NULL;
    this->createWindow = NULL;

}

ChooseOptionWindow::~ChooseOptionWindow()
{
    if (this->joinWindow != NULL)
        delete joinWindow;
    if (this->createWindow != NULL)
        delete createWindow;
    delete ui;
}

void ChooseOptionWindow::on_joinButton_clicked()
{
    this->joinWindow = new JoinWindow;
    hide();
    this->joinWindow->show();
}


void ChooseOptionWindow::on_createButton_clicked()
{
    this->createWindow = new CreateWindow;
    hide();
    this->createWindow->show();
}


void ChooseOptionWindow::on_joinButton_2_clicked()
{
    QApplication::quit();
}

