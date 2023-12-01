#include "createwindow.h"
#include "ui_createwindow.h"
#include <QMessageBox>

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
    //cl.getAvailableMatches();
    if (ui->matchNameTextEdit->text().size() == 0) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("error creating server");
        msgBox.exec();
        msgBox.setStyleSheet("QMessageBox { background-color: gray; border: 1px solid gray; }");

    } else {

        int result = this->cl.createNewMatch(
            ui->amtOfPlayersSpinBox->value(),
            ui->matchNameTextEdit->text().toStdString(),
            map
        );

        if (result == 0) {
            hide();
            this->cl.startGame();
            QApplication::quit();
        } else {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Error");
            msgBox.setText("error creating server");
            msgBox.exec();
            msgBox.setStyleSheet("QMessageBox { background-color: gray; border: 1px solid gray; }");
        }


    }


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

