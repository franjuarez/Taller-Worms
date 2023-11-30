#include "connectionwindow.h"
#include "./ui_connectionwindow.h"
#include "../client_src/client_lobby.h"
#include "../shared_src/info_struct.h"
#include <QMessageBox>
#include <utility>



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

    QString port = ui->portLineEdit->text();
    QString address = ui->addressLineEdit->text();
    //std::shared_ptr<InfoStruct> infoStruct = std::make_shared<InfoStruct>(port, address);
    //ClientLobby cl(infoStruct);


    try {

        //std::shared_ptr<InfoStruct> infoStruct = std::make_shared<InfoStruct>(address.toStdString(), port.toStdString());
        ClientLobby cl(address.toStdString(), port.toStdString());

        this->chooseOptionWindow = new ChooseOptionWindow(nullptr, std::move(cl));
        hide();
        this->chooseOptionWindow->show();
    
        //GameView gv(infoStruct);
        //gv.start();
        //gv.join();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        QMessageBox::warning(this, "Error" ,"error conecting to server");
    }
    


}
