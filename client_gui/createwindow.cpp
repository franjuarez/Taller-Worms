#include "createwindow.h"
#include "ui_createwindow.h"
#include <QMessageBox>


CreateWindow::CreateWindow(QWidget *parent, ClientLobby&& cl) :
        QDialog(parent),
        cl(std::move(cl)),
        ui(new Ui::CreateWindow)
{
    ui->setupUi(this);
    MapsLoader mapsLoader(CONFIG.getMapsFile());
    std::vector<std::string> mapNames = mapsLoader.getMapsNames();
    std::string defaultMapNames("dust2testsmallmediumsubsuelo de fiuba");

    for (std::string& mapName : mapNames) {
        if (defaultMapNames.find(mapName) == std::string::npos) {
            ui->comboBox->addItem(QString::fromStdString(mapName));
        }
    }

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
    }
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
        msgBox.setText("Match name can't be empty!!");
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
        } else if (result == 1) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Error");
            msgBox.setText("Match name already exists");
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


void CreateWindow::on_pushButton_clicked()
{
    if (ui->comboBox->currentIndex() == -1) {
        return;
    }
    createMatch(ui->comboBox->currentText().toStdString());
}

