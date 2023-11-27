#ifndef CREATEWINDOW_H
#define CREATEWINDOW_H

#include <QDialog>

namespace Ui {
class CreateWindow;
}

class CreateWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CreateWindow(QWidget *parent = nullptr);
    ~CreateWindow();

private:
    Ui::CreateWindow *ui;
};

#endif // CREATEWINDOW_H
