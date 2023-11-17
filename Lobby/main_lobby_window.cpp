#include "main_lobby_window.h"
#include "./ui_main_lobby_window.h"
#include "iostream"
#include "joinscreen.h"
#include "createscreen.h"

MainLobbyWindow::MainLobbyWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainLobbyWindow)
{
    ui->setupUi(this);
}

MainLobbyWindow::~MainLobbyWindow()
{
    delete ui;
}


void MainLobbyWindow::on_pushButton_3_clicked()
{
    JoinScreen js;
    js.show();
    this->hide();
    js.exec();
}


void MainLobbyWindow::on_pushButton_4_released()
{
    this->hide();
    QApplication::quit();

}


void MainLobbyWindow::on_pushButton_2_clicked()
{
    CreateScreen cs;
    cs.show();
    this->hide();
    cs.exec();
}

