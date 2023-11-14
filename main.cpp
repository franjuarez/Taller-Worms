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

//{
		//if (argc < 3){
//		throw std::runtime_error("Invalid arguments!");
//		return ERROR;
//	}
//
//	try {
//		
//		GameView gv(argv[1], argv[2]);
//		gv.start();
//		gv.join();
//	} catch (const std::exception& e) {
//		std::cerr << e.what() << std::endl;
//		return ERROR;
//	}
//	return SUCCESS;
//}
