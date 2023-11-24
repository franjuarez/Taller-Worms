#include "game_loop.h"

#define CONFIG ConfigLoader::getInstance()

#define RATE (1000.f / CONFIG.getFps())

GameLoop::GameLoop(Queue<std::shared_ptr<Command>>& commandsQueue, StatusBroadcaster& statusBroadcaster, std::shared_ptr<GameMap> gameMap, std::vector<Team> teams, bool* playing)
: commandsQueue(commandsQueue), statusBroadcaster(statusBroadcaster), gameWorld(gameMap), teams(teams), playing(playing) {
	this->teamPlayingID = 0;
	this->wormPlayingHealth = CONFIG.getWormInitialHealth();
	this->waitingForStatic = false;	
	this->waitingExtraTime = false;
	this->start_time = std::chrono::steady_clock::now();
	this->cheatOn = false;
}

void GameLoop::loopLogic(int64_t elapsed_time) {
// se encarga de los turnos y que jugador esta al momento.
// es el que se encarga de que gusano esta al momento

	std::shared_ptr<Command> command;
	while (commandsQueue.try_pop(command) && !waitingForStatic) {

			// agregarle un parametro extra a executeCommand para que no se 
			// ejecuten cosas q no sean de movimiento 
			waitingExtraTime = command->executeCommand(gameWorld, &cheatOn, waitingExtraTime);
			if (waitingExtraTime) {
				this->start_extra_time = std::chrono::steady_clock::now();
			}
	}

	gameWorld.update();
	std::shared_ptr<GameDynamic>gameDynamic(gameWorld.getGameStatus(wormPlayingID));
	if (waitingForStatic && !cheatOn) {
		gameDynamic->setWormPlayingID(NO_WORM_PLAYING);
	}
	
	std::vector<WormDTO> worms = gameDynamic->getWorms();
	int wormPlayingNewHealth;
	std::vector<int> teamsHealth(teams.size(), 0);
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
	statusBroadcaster.broadcast(gameDynamic);

	// std::cout << CONFIG.getTurnTime() << std::endl;

	if (waitingExtraTime) {
		auto current_time_t = std::chrono::steady_clock::now();
		auto extraTime = std::chrono::duration_cast<std::chrono::milliseconds>(current_time_t - this->start_extra_time).count();

		if (extraTime > CONFIG.getExtraTime() * 1000 ) {
			std::cout << extraTime << std::endl;
			waitingForStatic = true;
			waitingExtraTime = false;
		}
	}

	if ((wormPlayingHealth != wormPlayingNewHealth || elapsed_time > CONFIG.getTurnTime() * 1000 )) {
		waitingForStatic = true;
	}

	// std::cout << "cheatON " << cheatOn  << std::endl;

	if (waitingForStatic && !cheatOn) {
		if(gameWorld.allEntitiesAtRest()) {
			waitingForStatic = false;
			waitingExtraTime = false;
			changeWormPlaying(worms);
		}
	} else if (waitingForStatic && cheatOn) {
		if (gameWorld.allEntitiesAtRest()) {
			waitingForStatic = false;
			waitingExtraTime = false;
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

void GameLoop::changeWormPlaying(std::vector<WormDTO> worms) {
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
