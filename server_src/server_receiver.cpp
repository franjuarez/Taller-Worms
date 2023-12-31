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
        talking = false;
        return;
    } catch (const ClosedQueue& e){
        talking = false;
        return;
    } catch (const std::exception& e){
        talking = false;
        std::cout << "Error inesperado" << e.what() << std::endl;
        return;
    }
}

ServerReceiver::~ServerReceiver() {}
