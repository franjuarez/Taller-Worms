#include "joinwindow.h"
#include "ui_joinwindow.h"

JoinWindow::JoinWindow(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::JoinWindow)
{
    ui->setupUi(this);
    ui->availableMatchesComboBox->addItems(QStringList {"uno", "dos", "tres"});
}

JoinWindow::~JoinWindow()
{
    delete ui;
}
