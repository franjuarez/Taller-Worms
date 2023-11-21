#include "sender.h"
#include "../game_src/commands/command.h"
#include "../game_src/constants_game.h"
#include <iostream>

Sender::Sender(Protocol& protocol, Queue<std::shared_ptr<Command>>& q, bool& keepTalking) : protocol(protocol), 
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
            std::shared_ptr<Command> command = commandsQueue.pop();
            command->send(protocol);    
        }
    } catch (const ClosedSocket& e){
        std::cout << "Sender: Se ha cerrado la conexion\n";
        keepTalking = false;
    } catch (const ClosedQueue& e){
        std::cout << "Sender: Se ha cerrado la queue\n";
        keepTalking = false;
    } catch (std::exception& e){
        std::cout << "Error in receiver: " << e.what() << std::endl;
        keepTalking = false;
    } 
}

Sender::~Sender() {}