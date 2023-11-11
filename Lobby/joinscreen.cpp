#include "joinscreen.h"
#include "ui_joinscreen.h"
#include "iostream"
#include "../../ui_src/game_view.h"

JoinScreen::JoinScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JoinScreen)
{
    ui->setupUi(this);
}

JoinScreen::~JoinScreen()
{
    delete ui;
}


void JoinScreen::on_lineEdit_textEdited(const QString &arg1)
{
    //std::cout << arg1.toStdString() << std::endl;
    this->port = arg1;
}


void JoinScreen::on_pushButton_clicked()
{
    //std::cout << this->port.toStdString() << std::endl;
    //std::cout << this->address.toStdString() << std::endl;
    try {
    GameView gv(port.toStdString(), address.toStdString());

    gv.start();
    gv.join();

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return ERROR;
    }

}


void JoinScreen::on_lineEdit_2_textEdited(const QString &arg1)
{
    this->address = arg1;
}

