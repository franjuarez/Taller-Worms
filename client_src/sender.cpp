#include "sender.h"
#include "../game_src/select_map.h"
#include "../game_src/move.h"

#include <iostream>

Sender::Sender(Protocol& protocol, Queue<Command*>& q) : protocol(protocol), 
commandsQueue(q) {}

void Sender::run() {
    SelectMap* select = new SelectMap(9, NO_WORM_PLAYING, "aloha" );
    commandsQueue.push(select);
    Move* move = new Move(9);
    commandsQueue.push(move);
    //  yyyyyy aca mando los comandos 
    // como se decidiran los comandos lo sabe dios nomas
    // 2do empieza el game loop
    // todos los comandos son de la clase Command
    try {
        // 1ro mando el chosen map
        while (1) {
            Command* command = commandsQueue.pop();
            command->send(protocol);    
        }
    } catch (...) {
        std::cout << "AAAAAAAAAAAAA\n";
    } 
}

Sender::~Sender() {}