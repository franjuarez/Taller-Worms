#ifndef MAINLOBBYWINDOW_H
#define MAINLOBBYWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainLobbyWindow; }
QT_END_NAMESPACE

class MainLobbyWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainLobbyWindow(QWidget *parent = nullptr);
    ~MainLobbyWindow();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_released();

    void on_pushButton_2_clicked();

private:
    Ui::MainLobbyWindow *ui;
};
#endif // MAINLOBBYWINDOW_H
