#include "createscreen.h"
#include "ui_createscreen.h"
#include "iostream"
#include  "../server_src/lobby.cpp"

CreateScreen::CreateScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateScreen)
{
    ui->setupUi(this);
}

CreateScreen::~CreateScreen()
{
    delete ui;
}

void CreateScreen::on_pushButton_clicked()
{
    QString port = ui->lineEdit->text();
    QString map = ui->comboBox->currentText();
    int players = ui->spinBox->value();

    Lobby lobby(port.toStdString() , players, map.toStdString());
    lobby.run();
    //std::cout << port.toStdString() << std::endl;
    //std::cout << map.toStdString() << std::endl;
    //std::cout << players << std::endl;
}

