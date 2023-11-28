#ifndef CREATEWINDOW_H
#define CREATEWINDOW_H

#include <QDialog>
#include "../client_src/client_lobby.h"

namespace Ui {
class CreateWindow;
}

class CreateWindow : public QDialog
{
    Q_OBJECT

public:
    CreateWindow(QWidget *parent, ClientLobby&& cl);
    ~CreateWindow();

private slots:
    void on_dedustButton_clicked();

    void on_testButton_clicked();

    void on_smallButton_clicked();

    void on_mediumButton_clicked();

    void on_subsueloButton_clicked();

private:
    ClientLobby cl;
    Ui::CreateWindow *ui;

    void createMatch(std::string map);
};

#endif // CREATEWINDOW_H
