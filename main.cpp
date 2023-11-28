#include "connectionwindow.h"
#include <QApplication>
#include <iostream>

#define ERROR 1
#define SUCCESS 0

int main(int argc, char** argv) {
	QApplication a(argc, argv);
    ConnectionWindow w;
    w.setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    w.show();
    return a.exec();
}
