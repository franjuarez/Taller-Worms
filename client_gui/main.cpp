#include "connectionwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    try {
        QApplication a(argc, argv);
        ConnectionWindow w;
        w.setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
        w.show();
        return a.exec();
    } catch (const std::exception& e) {
        std::cerr << "abracadabra" << e.what() << std::endl;
        return 1;
    }
}
