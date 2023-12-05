#include "joinwindow.h"
#include "ui_joinwindow.h"
#include <vector>
#include <string>
#include <map>
#include <QMessageBox>


JoinWindow::JoinWindow(QWidget *parent, ClientLobby&& cl) :
        QDialog(parent),
        cl(std::move(cl)),
        ui(new Ui::JoinWindow)
{
    ui->setupUi(this);
    std::map<std::string, std::string> matchNames = cl.getAvailableMatches();
    for (auto it = matchNames.begin(); it != matchNames.end(); it++) {
        if (it->second == "") {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Error");
            msgBox.setText("Server closed");
            msgBox.exec();
            msgBox.setStyleSheet("QMessageBox { background-color: gray; border: 1px solid gray; }");
            QApplication::quit();
        }
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
    std::map<std::string, std::string> matchNames = cl.getAvailableMatches();
    for (auto it = matchNames.begin(); it != matchNames.end(); it++) {
        if (it->second == "") {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Error");
            msgBox.setText("Server closed");
            msgBox.exec();
            msgBox.setStyleSheet("QMessageBox { background-color: gray; border: 1px solid gray; }");
            QApplication::quit();
        }
        ui->availableMatchesComboBox->addItem(QString::fromStdString(it->first));
    }

}


void JoinWindow::on_joinButton_clicked()
{
    if (ui->availableMatchesComboBox->currentIndex() == -1) {
        return;
    }
    hide();
        int result = this->cl.joinMatch(ui->availableMatchesComboBox->currentText().toStdString());
        if (result == 0) {
            hide();
            this->cl.startGame();
            QApplication::quit();
        } else if (result == 1) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Error");
            msgBox.setText("Error creating server");
            msgBox.exec();
            msgBox.setStyleSheet("QMessageBox { background-color: gray; border: 1px solid gray; }");
        } else if (result == 2) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Error");
            msgBox.setText("Server closed");
            msgBox.exec();
            msgBox.setStyleSheet("QMessageBox { background-color: gray; border: 1px solid gray; }");
            QApplication::quit();
        }

}

