#ifndef CHOOSEOPTIONWINDOW_H
#define CHOOSEOPTIONWINDOW_H

#include <QDialog>
#include "joinwindow.h"
#include "createwindow.h"
#include "../client_src/client_lobby.h"

namespace Ui {
class ChooseOptionWindow;
}

class ChooseOptionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseOptionWindow(QWidget *parent, ClientLobby&& cl);
    ~ChooseOptionWindow();

private slots:
    void on_joinButton_clicked();

    void on_createButton_clicked();

    void on_joinButton_2_clicked();

private:
    ClientLobby cl;
    Ui::ChooseOptionWindow *ui;
    CreateWindow *createWindow;
    JoinWindow *joinWindow;
};

#endif // CHOOSEOPTIONWINDOW_H
