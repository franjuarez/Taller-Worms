#include "game_loop.h"
#include <chrono>
#include "../game_src/game_dynamic.h"
#include "../game_src/worm_dto.h"
#include "../game_src/beam_dto.h"
#include "../game_src/game_map.h"
#include <unistd.h>

#define FPS 60.0f
#define RATE (1000.f / FPS)  

GameLoop::GameLoop(Queue<Command*>& commandsQueue, StatusBroadcaster& statusBroadcaster)
: commandsQueue(commandsQueue), statusBroadcaster(statusBroadcaster), gameWorld() {}

// static uint32 getTicks()
// {
//     static clock_t start_time = 0;
//     if (start_time == 0) {
//         start_time = clock();
//     }

//     clock_t current_time = clock();
//     return (current_time - start_time) * 1000 / CLOCKS_PER_SEC;
// }

void GameLoop::loopLogic() {
// se encarga de los turnos y que jugador esta al momento.
// es el que se encarga de que gusano esta al momento
	Command* command;
	while (commandsQueue.try_pop(command)) {
			command->executeCommand(gameWorld);
	}
	gameWorld.update();
	GameDynamic* gameDynamic = gameWorld.getGameStatus(0);
	statusBroadcaster.broadcast(gameDynamic);
}

void GameLoop::start() {
	// int t1 = getTicks();
        //get ticks without sdl
	//float durationInSeconds;


    std::vector<BeamDTO> beams;
    std::vector<WormDTO> worms;
    Position pos(9.7, 11.0);
    Position pos2(9.89, 12.1);
    worms.push_back(WormDTO(0, 0, 79, 1, pos2));
    //worms.push_back(WormDTO(1, 0, 9, 1, pos2));

    //createBeam(10.0f, 10.0f, 0, true);
    //createWorm(10.0f, 15.0f, 0, 0);
    //createWorm(12.0f, 12.0f, 1, 1);

    beams.push_back(BeamDTO(6, Position(10.0f, 10.0f), 0));
	beams.push_back(BeamDTO(6, Position(16.0f, 8.0f), 0));
	beams.push_back(BeamDTO(6, Position(22.0f, 6.0f), 0));
	beams.push_back(BeamDTO(6, Position(28.0f, 4.0f), 0));
	beams.push_back(BeamDTO(6, Position(34.0f, 2.0f), 0));
	beams.push_back(BeamDTO(6, Position(40.0f, 0.0f), 0));
	beams.push_back(BeamDTO(6, Position(46.0f, -2.0f), 0));

    //beams.push_back(BeamDTO(3, Position(10.0f, 12.0f), 0));
	//beams.push_back(BeamDTO(6, Position(15.0f, 5.0f), 50));
	//beams.push_back(BeamDTO(3, Position(10.0f, 3.0f), -10));
    //beams.push_back(BeamDTO(6, pos2, 10.66));
    GameMap* map = new GameMap("aloha", beams, worms);
    statusBroadcaster.broadcast(map); 

	while(true) {
		loopLogic();
		usleep(RATE*1000);
    
		// int t2 = getTicks();
		// float rest = RATE - (t2 - t1);
// 
		// if (rest < 0) { //me tomo mas tiempo del que tenia
			// int behind = -rest; //behind -> por cuanto me pase
			// 
			//lo que deberia dormir para despertar justo en el inicio de la ventana de un frame
			//// rest = RATE - fmod(behind, RATE);
// 
			//la cantidad de frames que me saltie y que por ende, deberia dormir
			// float lost = behind + rest;
			// t1 += lost;
			////i += (int )(lost / RATE);
            // for (int k = 0; k < (int)(lost / RATE); k++) {
				// std::vector<WormDTO> worms = gameWorld.update();
				// GameDynamic* gameDynamic = new GameDynamic(0, worms);
				// statusBroadcaster.broadcast(gameDynamic);
            // }
		// }
        // 
		// t1 += RATE; //le sume lo perdido y la rate asique esta actualizado
		// usleep(rest * 100);
	}
}

GameLoop::~GameLoop() {}
