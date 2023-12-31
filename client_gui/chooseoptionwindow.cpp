#include "chooseoptionwindow.h"
#include "ui_chooseoptionwindow.h"

ChooseOptionWindow::ChooseOptionWindow(QWidget *parent, ClientLobby&& cl) :
        QDialog(parent),
        cl(std::move(cl)),
        ui(new Ui::ChooseOptionWindow)
{
    ui->setupUi(this);
    this->joinWindow = NULL;
    this->createWindow = NULL;
    this->aboutWindow = NULL;

}

ChooseOptionWindow::~ChooseOptionWindow()
{
    if (this->createWindow != NULL)
        delete createWindow;
    if (this->joinWindow != NULL)
        delete joinWindow;
    if (this->aboutWindow != NULL)
        delete aboutWindow;
    delete ui;
}

void ChooseOptionWindow::on_joinButton_clicked()
{
    this->joinWindow = new JoinWindow(nullptr, std::move(this->cl));
    hide();
    this->joinWindow->show();
}


void ChooseOptionWindow::on_createButton_clicked()
{
    this->createWindow = new CreateWindow(nullptr, std::move(this->cl));
    hide();
    this->createWindow->show();
}


void ChooseOptionWindow::on_joinButton_2_clicked()
{
    QApplication::quit();
}


void ChooseOptionWindow::on_createButton_2_clicked()
{
    this->aboutWindow = new AboutWindow;
    hide();
    this->aboutWindow->show();
}

