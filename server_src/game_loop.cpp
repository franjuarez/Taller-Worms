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


	if (waitingExtraTime) {
		auto current_time_t = std::chrono::steady_clock::now();
		auto extraTime = std::chrono::duration_cast<std::chrono::milliseconds>(current_time_t - this->start_extra_time).count();


		if (extraTime > CONFIG.getExtraTime() * 1000 ) {
			waitingForStatic = true;
			waitingExtraTime = false;
			stillWaiting = false;
		}
	}

	if ((wormPlayingHealth != wormPlayingNewHealth || elapsed_time > CONFIG.getTurnTime() * 1000 )) {
		waitingForStatic = true;
	}


	if (waitingForStatic && !cheatOn) {
		if(gameWorld.allEntitiesAtRest()) {
			waitingForStatic = false;
			waitingExtraTime = false;
			stillWaiting = false;
			changeWormPlaying(worms);
		}
	} else if (waitingForStatic && cheatOn) {
		if (gameWorld.allEntitiesAtRest()) {
			waitingForStatic = false;
			waitingExtraTime = false;
			stillWaiting = false;
		}
	} 

}

void GameLoop::run() {
	this->wormPlayingID = teams[teamPlayingID].getNextWormID();
	while(*playing && !gameOver) {
		auto current_time = std::chrono::steady_clock::now();
		auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - this->start_time).count();
		try {
			loopLogic(elapsed_time);
			usleep(RATE*1000);
		} catch (const ClosedQueue& e){
        	std::cout << "Reciever: Se ha cerrado la QUEUE\n";
			return;
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
		return teamPlayingID;
	}
	gameOver = true;
	return ALL_LOST;
}


GameLoop::~GameLoop() {}
