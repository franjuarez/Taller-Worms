#include "sender.h"
#include "../game_src/select_map.h"
#include "../game_src/move.h"
#include "../game_src/constants_game.h"
#include <iostream>

Sender::Sender(Protocol& protocol, Queue<Command*>& q, bool& keepTalking) : protocol(protocol), 
commandsQueue(q), keepTalking(keepTalking) {}

void Sender::run() {
    // SelectMap* select = new SelectMap(9, NO_WORM_PLAYING, "aloha" );
    // commandsQueue.push(select);
    //  yyyyyy aca mando los comandos 
    // como se decidiran los comandos lo sabe dios nomas
    // 2do empieza el game loop
    // todos los comandos son de la clase Command
    try {
        // 1ro mando el chosen map
        while (keepTalking) {
            Command* command = commandsQueue.pop();
            command->send(protocol);    
        }
    } catch (...) {
        keepTalking = false;
        return;
    } 
}

Sender::~Sender() {}