#ifndef CONNECTIONWINDOW_H
#define CONNECTIONWINDOW_H

#include <QMainWindow>
#include "chooseoptionwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ConnectionWindow; }
QT_END_NAMESPACE

class ConnectionWindow : public QMainWindow
{
    Q_OBJECT

public:
    ConnectionWindow(QWidget *parent = nullptr);
    ~ConnectionWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ConnectionWindow *ui;
    ChooseOptionWindow *chooseOptionWindow;
};
#endif // CONNECTIONWINDOW_H
