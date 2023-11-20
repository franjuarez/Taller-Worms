#include "server_receiver.h"
#include "../shared_src/protocol.h"
#include "../game_src/commands/command.h"

ServerReceiver::ServerReceiver(Protocol& protocol, Queue<std::shared_ptr<Command>>& commandsQueue, bool& talking) 
: protocol(protocol), commandsQueue(commandsQueue), talking(talking) {}

void ServerReceiver::run() {
    try{
        while (talking) {
            std::shared_ptr<Command> command = protocol.receiveCommand();
            commandsQueue.push(command);
        }
    } catch (const ClosedSocket& e){
        std::cout << "Reciever: Se ha cerrado la conexion\n";
        talking = false;
    } catch (const ClosedQueue& e){
        std::cout << "Reciever: Se ha cerrado la QUEUE\n";
        talking = false;
    } catch (const std::exception& e){
        talking = false;
        std::cout << "Error inesperado" << e.what() << std::endl;
    }
}

ServerReceiver::~ServerReceiver() {}
