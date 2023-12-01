#include "joinwindow.h"
#include "ui_joinwindow.h"
#include <vector>
#include <string>
#include <map>


JoinWindow::JoinWindow(QWidget *parent, ClientLobby&& cl) :
        QDialog(parent),
        cl(std::move(cl)),
        ui(new Ui::JoinWindow)
{
    ui->setupUi(this);
    std::map<std::string, std::string> matchNames = cl.getAvailableMatches();
    for (auto it = matchNames.begin(); it != matchNames.end(); it++) {
        std::cout << it->first << std::endl;
        ui->availableMatchesComboBox->addItem(QString::fromStdString(it->first));
        
    }
}

JoinWindow::~JoinWindow()
{
    delete ui;
}

void JoinWindow::on_refreshButton_clicked()
{
    ui->availableMatchesComboBox->clear();
    //cl.refresh();
    std::map<std::string, std::string> matchNames = cl.getAvailableMatches();
    for (auto it = matchNames.begin(); it != matchNames.end(); it++) {
        ui->availableMatchesComboBox->addItem(QString::fromStdString(it->first));
    }

}


void JoinWindow::on_joinButton_clicked()
{
    hide();
    this->cl.joinMatch(ui->availableMatchesComboBox->currentText().toStdString());
    QApplication::quit();

}

