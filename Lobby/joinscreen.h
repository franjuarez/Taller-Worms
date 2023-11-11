#ifndef JOINSCREEN_H
#define JOINSCREEN_H

#include <QDialog>

namespace Ui {
class JoinScreen;
}

class JoinScreen : public QDialog
{
    Q_OBJECT
    QString port;
    QString address;

public:
    explicit JoinScreen(QWidget *parent = nullptr);
    ~JoinScreen();

private slots:


    void on_lineEdit_textEdited(const QString &arg1);

    void on_pushButton_clicked();

    void on_lineEdit_2_textEdited(const QString &arg1);

private:
    Ui::JoinScreen *ui;
};

#endif // JOINSCREEN_H
