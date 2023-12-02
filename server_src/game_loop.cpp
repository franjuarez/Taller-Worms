#include "game_loop.h"
#include "status_broadcaster.h"
#include "../game_src/commands/command.h"
#include "../game_src/constants_game.h"

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


void GameLoop::run() {
	this->wormPlayingID = teams[teamPlayingID].getNextWormID();
	while(*playing && !gameOver) {
		auto current_time = std::chrono::steady_clock::now();
		auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - this->start_time).count();
		try {
			loopLogic(elapsed_time);
			usleep(RATE*1000);
			checkPlayers();
		} catch (const ClosedQueue& e){
        	std::cout << "Reciever: Se ha cerrado la QUEUE\n";
			return;
    	} catch (std::exception& e) {
			std::cout << "Error in game loop: " << e.what() << std::endl;
			return;
		}
	}
}


void GameLoop::loopLogic(int64_t elapsed_time) {
	std::shared_ptr<Command> command;
	while (commandsQueue.try_pop(command) && !waitingForStatic) {
			waitingExtraTime = command->executeCommand(gameWorld, &cheatOn, waitingExtraTime);
			if (waitingExtraTime && !stillWaiting) {
				this->start_extra_time = std::chrono::steady_clock::now();
				stillWaiting = true;
			}
	}

	gameWorld.update();
	std::shared_ptr<GameDynamic>gameDynamic(gameWorld.getGameStatus(wormPlayingID));
	std::vector<WormDTO> worms = gameDynamic->getWorms();
	int wormPlayingNewHealth = updateGameDynamic(gameDynamic, worms);

	if (gameOver) {
		return;
	}

	if (waitingExtraTime) {
		auto current_time_t = std::chrono::steady_clock::now();
		auto extraTime = std::chrono::duration_cast<std::chrono::milliseconds>(current_time_t - this->start_extra_time).count();

		if (extraTime > CONFIG.getExtraTime() * 1000 ) {
			waitingForStatic = true;
			waitingExtraTime = false;
			stillWaiting = false;
		}
	}


	if (wormPlayingHealth > wormPlayingNewHealth || elapsed_time > CONFIG.getTurnTime() * 1000 ) {
		waitingForStatic = true;
	} else if (wormPlayingHealth < wormPlayingNewHealth) {
		wormPlayingHealth = wormPlayingNewHealth;
	}


	if (waitingForStatic && !cheatOn) {

		if (gameWorld.allEntitiesAtRest() && !waitingForBox) {
			waitingForBox = dropSupplyBox();
			if (!waitingForBox) {
				reset();
				changeWormPlaying(worms);
			}
		}

		if(gameWorld.allEntitiesAtRest() && waitingForBox) {
			reset();
			changeWormPlaying(worms);
		}

	} else if (waitingForStatic && cheatOn) {
		if (gameWorld.allEntitiesAtRest()) {
			reset();
		}
	} 

}


int GameLoop::updateGameDynamic(std::shared_ptr<GameDynamic> gameDynamic, std::vector<WormDTO> worms) {
	if (waitingForStatic && !cheatOn) {
		gameDynamic->setWormPlayingID(NO_WORM_PLAYING);
	}
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

	return wormPlayingNewHealth;
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
	int teamWinning = -1;
	for (size_t i = 0; i < teams.size(); i++) {
		if (teams[i].hasWorms()) {
			teamsWithWorms++;
			teamWinning = i;
		}
	}

	if (teams.size() == 1) {
		if (teamsWithWorms == 1) {
			return PLAYING;
		}
		gameOver = true;
		return ALL_LOST;
	}

	if (teamsWithWorms > 1) {
		return PLAYING;
	} else if (teamsWithWorms == 1) {
		gameOver = true;
		return teamWinning;
	}
	gameOver = true;
	return ALL_LOST;
}


void GameLoop::reset() {
	waitingForStatic = false;
	waitingForBox = false;
	waitingExtraTime = false;
	stillWaiting = false;

}

void GameLoop::checkPlayers() {
	if (statusBroadcaster.isEmpty()) {
		gameOver = true;
	}
}


int GameLoop::dropSupplyBox() {
	if (shouldDropBox()) {
		int type = decideTypeOfSupplyBox();
		gameWorld.dropSupplyBox(type);
		return 1;
	}
	return 0;
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
        CONFIG.getDynamiteAmmoProbability(),
        CONFIG.getAirAttackAmmoProbability(),
        CONFIG.getHolyGrenadeAmmoProbability()
    };

    std::discrete_distribution<> distrib(weights.begin(), weights.end());

    int randomIndex = distrib(gen);

    switch(randomIndex) {
        case 0: return MORTAR_SUPPLY;
        case 1: return RED_GRENADE_SUPPLY;
        case 2: return REMOTE_OPERATED_SUPPLY;
        case 3: return BAT_SUPPLY;
        case 4: return BANANA_SUPPLY;
        case 5: return DYNAMITE_SUPPLY;
        case 6: return AIR_ATTACK_SUPPLY;
        case 7: return HOLY_GRENADE_SUPPLY;
        default: return REMOTE_OPERATED_SUPPLY; // por ahora que no estan todas las armas
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

GameLoop::~GameLoop() {}
