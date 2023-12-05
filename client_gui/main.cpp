#include "connectionwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConnectionWindow w;
    w.setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    w.show();
    return a.exec();

}
