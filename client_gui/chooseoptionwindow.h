#ifndef CHOOSEOPTIONWINDOW_H
#define CHOOSEOPTIONWINDOW_H

#include <QDialog>
#include "joinwindow.h"
#include "createwindow.h"

namespace Ui {
class ChooseOptionWindow;
}

class ChooseOptionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseOptionWindow(QWidget *parent = nullptr);
    ~ChooseOptionWindow();

private slots:
    void on_joinButton_clicked();

    void on_createButton_clicked();

    void on_joinButton_2_clicked();

private:
    Ui::ChooseOptionWindow *ui;
    JoinWindow *joinWindow;
    CreateWindow *createWindow;
};

#endif // CHOOSEOPTIONWINDOW_H
