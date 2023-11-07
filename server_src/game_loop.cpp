#include "game_loop.h"
#include <chrono>
#include "../game_src/game_dynamic.h"

#define SLEEP_TIME 1/60

GameLoop::GameLoop(Queue<Command*>& commandsQueue, StatusBroadcaster& statusBroadcaster)
: commandsQueue(commandsQueue), statusBroadcaster(statusBroadcaster), gameWorld() {}

void GameLoop::start() {

// en un brillante while 
// se encarga de los turnos y que jugador esta al momento.
// es el que se encarga de que gusano esta al momento
        while (true) {
                Command* command;
                // 1 pop un command
                //  -> es un try-pop
                if (commandsQueue.try_pop(command)) {
                        // 2.0 pasar a monke
                        //  -> execute recibe la ref de GameWorld y hace tipo el send
                        command->executeCommand(gameWorld);
                }
                
                // 3 push un Dynamic
                //  -> Update devuelve los estados de las cosas para ser pusheadas :)
        // monke devuelve un vector de WormDto
        // -> aca se crea el Dynamic
        std::vector<WormDTO> worms = gameWorld.update();
        GameDynamic* gameDynamic = new GameDynamic(0, worms);
        statusBroadcaster.broadcast(gameDynamic);
        std::this_thread::sleep_for(std::chrono::seconds(SLEEP_TIME));
        // requerimos un sleep para no matar la compu wiiiii 
        }
}

GameLoop::~GameLoop() {}
