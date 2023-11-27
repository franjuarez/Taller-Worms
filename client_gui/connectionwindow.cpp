#include "connectionwindow.h"
#include "./ui_connectionwindow.h"


ConnectionWindow::ConnectionWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::ConnectionWindow)
{
    ui->setupUi(this);
    this->chooseOptionWindow = NULL;

}

ConnectionWindow::~ConnectionWindow()
{
    if (this->chooseOptionWindow != NULL)
        delete this->chooseOptionWindow;

    delete ui;
}


void ConnectionWindow::on_pushButton_clicked()
{
    this->chooseOptionWindow = new ChooseOptionWindow;
    hide();
    this->chooseOptionWindow->show();

}

