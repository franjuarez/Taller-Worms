#include "joinscreen.h"
#include "ui_joinscreen.h"
#include "iostream"
#include "../ui_src/game_view.h"
#define ERROR


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
    this->port = arg1;
}


void JoinScreen::on_pushButton_clicked()
{
    try {
    GameView gv(address.toStdString(), port.toStdString());
    this->hide();

    gv.start();
    gv.join();
    QApplication::quit();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

}


void JoinScreen::on_lineEdit_2_textEdited(const QString &arg1)
{
    this->address = arg1;
}

