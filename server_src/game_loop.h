#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include <vector>
#include <string>
#include <iostream>

#include "lobby.h"
#include "../shared_src/queue.h"
#include "../shared_src/thread.h"
#include "../shared_src/socket.h"


class GameLoop {

private: 
    Queue<Command>& commandsQueue; // esta saca los comandos con try pop porque no la deberia bloquear y siempre tiene que estar loopeando
    StatusBroadcaster& statusBroadcaster;
public:
    GameLoop(Queue<Command>& commandsQueue, StatusBroadcaster& statusBroadcaster);
    ~GameLoop();
    void start();
};
#endif