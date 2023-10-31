#include "sender.h"

#include <iostream>

Sender::Sender(Protocol& protocol, Queue<Command>& q) : protocol(protocol), 
commandsQueue(q) {}

void Sender::run() {
    std::cout << "Sender running\n";
    //  yyyyyy aca mando los comandos 
    // como se decidiran los comandos lo sabe dios nomas
    // 1ro mando el chosen map
    // 2do empieza el game loop
    // todos los comandos son de la clase Command
    try {
        // while (1) {
        // Command command = commandsQueue.pop();
        // protocol.sendCommand(command);
        // }
    } catch (...) {
        std::cout << "AAAAAAAAAAAAA\n";
    } 
}

Sender::~Sender() {}