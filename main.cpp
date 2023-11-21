#include "main_lobby_window.h"
#include <QApplication>
#include <iostream>

#define ERROR 1
#define SUCCESS 0

int main(int argc, char** argv) {
	QApplication a(argc, argv);
    MainLobbyWindow w;
    w.show();
    return a.exec();
}
