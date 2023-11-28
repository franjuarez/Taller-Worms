#include "createwindow.h"
#include "ui_createwindow.h"

CreateWindow::CreateWindow(QWidget *parent, ClientLobby&& cl) :
        QDialog(parent),
        cl(std::move(cl)),
        ui(new Ui::CreateWindow)
{
    ui->setupUi(this);
}


CreateWindow::~CreateWindow()
{
    delete ui;
}

void CreateWindow::createMatch(std::string map) {
    cl.getAvailableMatches();
    hide();
    this->cl.createNewMatch(
        ui->amtOfPlayersSpinBox->value(),
        ui->matchNameTextEdit->text().toStdString(),
        map);

    QApplication::quit();
    //std::cout << "sale de la funcion" << std::endl;

}

void CreateWindow::on_dedustButton_clicked()
{
    createMatch("dust2");
}


void CreateWindow::on_testButton_clicked()
{
    createMatch("test");
}


void CreateWindow::on_smallButton_clicked()
{
    createMatch("small");
}


void CreateWindow::on_mediumButton_clicked()
{
    createMatch("medium");
}


void CreateWindow::on_subsueloButton_clicked()
{
    createMatch("subsuelo de fiuba");
}

