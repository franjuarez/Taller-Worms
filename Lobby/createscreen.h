#ifndef CREATESCREEN_H
#define CREATESCREEN_H

#include <QDialog>

namespace Ui {
class CreateScreen;
}

class CreateScreen : public QDialog
{
    Q_OBJECT

public:
    explicit CreateScreen(QWidget *parent = nullptr);
    ~CreateScreen();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CreateScreen *ui;
    bool playing;
};

#endif
