#include "game_loop.h"
#include "../game_src/constants_game.h"

#define CONFIG ConfigLoader::getInstance()

#define RATE (1000.f / CONFIG.getFps())

GameLoop::GameLoop(Queue<std::shared_ptr<Command>>& commandsQueue, StatusBroadcaster& statusBroadcaster, std::shared_ptr<GameMap> gameMap, std::vector<Team> teams, bool* playing)
: commandsQueue(commandsQueue), statusBroadcaster(statusBroadcaster), gameWorld(gameMap), teams(teams), playing(playing) {
	this->teamPlayingID = 0;
	this->wormPlayingHealth = 100;
	this->waitingForStatic = false;
	this->start_time = std::chrono::steady_clock::now();
	this->cheatOn = false;
}

void GameLoop::loopLogic(int64_t elapsed_time) {
// se encarga de los turnos y que jugador esta al momento.
// es el que se encarga de que gusano esta al momento

	std::shared_ptr<Command> command;
	while (commandsQueue.try_pop(command) && !waitingForStatic) {
			waitingForStatic = command->executeCommand(gameWorld, &cheatOn);
	}
	gameWorld.update();

 
	std::shared_ptr<GameDynamic>gameDynamic(gameWorld.getGameStatus(wormPlayingID));
	if (waitingForStatic && !cheatOn) {
		gameDynamic->setWormPlayingID(NO_WORM_PLAYING);
	}
	
	std::vector<WormDTO> worms = gameDynamic->getWorms();
	int wormPlayingNewHealth;
	std::vector<uint32_t> teamsHealth(teams.size(), 0);
	for (size_t i = 0; i < worms.size(); i++) {

		teamsHealth[worms[i].getTeam()] += worms[i].getHealth();
		
		int wormId = worms[i].getId();

		if (wormId == wormPlayingID) {
			wormPlayingNewHealth = worms[i].getHealth();
		}

		int wormTeam = worms[i].getTeam();
		if (!worms[i].isAlive() && teams[wormTeam].checkWormExists(wormId)) {
			teams[wormTeam].removeWormID(wormId);
		}
	}

	
	gameDynamic->setTeamsHealth(teamsHealth);
	int winnerStatus = updateWinningStatus();
	gameDynamic->setWinnerTeam(winnerStatus);
	gameDynamic->setStatus(STARTED);

	statusBroadcaster.broadcast(gameDynamic);

	if (wormPlayingHealth != wormPlayingNewHealth || elapsed_time > CONFIG.getTurnTime() * 1000 ) {
		waitingForStatic = true;
	}

	// std::cout << "cheatON " << cheatOn  << std::endl;

	if (waitingForStatic && !cheatOn) {
		if(gameWorld.allEntitiesAtRest()) {
			waitingForStatic = false;
			changeWormPlaying(worms);
		}
	} else if (waitingForStatic && cheatOn) {
		if (gameWorld.allEntitiesAtRest()) {
			waitingForStatic = false;
		}
	} 

}

void GameLoop::run() {
	this->wormPlayingID = teams[teamPlayingID].getNextWormID();
	while(playing) {
		auto current_time = std::chrono::steady_clock::now();
		auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - this->start_time).count();
		try {
			loopLogic(elapsed_time);
			usleep(RATE*1000);
		} catch (std::exception& e) {
			std::cout << "Error in game loop: " << e.what() << std::endl;
			return;
		}
	}
}


int GameLoop::decideAmmoType() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<float> weights = {
        CONFIG.getMortarAmmoProbability(),
        CONFIG.getRedGrenadeAmmoProbability(),
        CONFIG.getTeleportAmmoProbability(),
        CONFIG.getBatAmmoProbability(),
        CONFIG.getBananaAmmoProbability(),
        // CONFIG.getDynamiteAmmoProbability(),
        // CONFIG.getAirAttackAmmoProbability(),
        // CONFIG.getHolyGrenadeAmmoProbability()
    };

    std::discrete_distribution<> distrib(weights.begin(), weights.end());

    int randomIndex = distrib(gen);

	std::cout << "Tipo de arma: " << randomIndex << std::endl;
    switch(randomIndex) {
        case 0: return MORTAR_SUPPLY;
        case 1: return RED_GRENADE_SUPPLY;
        case 2: return TELEPORT_SUPPLY;
        case 3: return BAT_SUPPLY;
        case 4: return BANANA_SUPPLY;
        // case 5: return DYNAMITE_SUPPLY;
        // case 6: return AIR_ATTACK_SUPPLY;
        // case 7: return HOLY_GRENADE_SUPPLY;
        default: return TELEPORT_SUPPLY; // por ahora que no estan todas las armas
    }
}


int GameLoop::decideTypeOfSupplyBox() {
   std::random_device rd;
   std::mt19937 gen(rd());

   std::vector<float> weights = {
       CONFIG.getSupplyBoxHealthProbability(),
       CONFIG.getSupplyBoxAmmoProbability(),
       CONFIG.getSupplyBoxTrapProbability()
   };

   std::discrete_distribution<> distrib(weights.begin(), weights.end());

   int randomIndex = distrib(gen);
	std::cout << "Tipo de supply: " << randomIndex << std::endl;
   switch(randomIndex) {
       case 0: return HEALTH_SUPPLY;
       case 1: return decideAmmoType();
       case 2: return TRAP_SUPPLY;
       default: return HEALTH_SUPPLY; // por defecto, en caso de que no coincida con ninguno de los casos
   }
}

bool GameLoop::shouldDropBox() {
   std::random_device rd;
   std::mt19937 gen(rd());

   float probability = CONFIG.getSupplyBoxProbability();

   std::discrete_distribution<> distrib({1 - probability, probability});

   int randomIndex = distrib(gen);

   return randomIndex == 1;
}


void GameLoop::changeWormPlaying(std::vector<WormDTO> worms) {
	if(shouldDropBox()){
		std::cout << "Tiro cajinha" << std::endl;
		int type = decideTypeOfSupplyBox();
		this->gameWorld.dropSupplyBox(type);
	} else{
		std::cout << "No tiro cajinha" << std::endl;
	}
	// std::cout << "cambiando turno! Tiro cajinha" << std::endl;
	// this->gameWorld.dropSupplyBox(HEALTH_SUPPLY);
	// std::cout << "termino la cajinha" << std::endl;
	teamPlayingID = (teamPlayingID + 1) % teams.size();

	for(size_t i = teamPlayingID; true ; i = (i + 1) % teams.size()){
		if(teams[i].hasWorms()){
			teamPlayingID = i;
			break;
		}

	}

	wormPlayingID = teams[teamPlayingID].getNextWormID();
	for (size_t i = 0; i < worms.size(); i++) {
		if (worms[i].getId() == wormPlayingID) {
			this->wormPlayingHealth = worms[i].getHealth();
			break;
		}
	}
	this->start_time = std::chrono::steady_clock::now();
	// std::cout << "Changing Turn! Team: " << teamPlayingID << " Worm: " << wormPlayingID << std::endl;
}

int GameLoop::updateWinningStatus() {
	int teamsWithWorms = 0;
	for (size_t i = 0; i < teams.size(); i++) {
		if (teams[i].hasWorms()) {
			teamsWithWorms++;
		}
	}

	if (teamsWithWorms > 1) {
		return PLAYING;
	} else if (teamsWithWorms == 1) {
		return teamPlayingID;
	}

	return ALL_LOST;
}

GameLoop::~GameLoop() {}
