#include "main_lobby_window.h"
#include "ui_src/game_view.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainLobbyWindow w;
    w.show();
    return a.exec();
}
