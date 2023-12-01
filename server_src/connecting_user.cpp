#include "connecting_user.h"
#include "../game_src/game_info.h"
#include "../game_src/commands/match_command.h"
#include "../shared_src/info_struct.h"


ConnectingUser::ConnectingUser(std::shared_ptr<InfoStruct> infoStruct, MatchesMonitor& matchesMonitor, bool* playing) : 
status(ACTIVE), infoStruct(infoStruct), matchesMonitor(matchesMonitor), playing(playing) {}


void ConnectingUser::run() {
    try {
        // GameInfo info(matchesMonitor.showMatchesAvailable());
        // infoStruct->prot.sendInfo(&info);

        while (status == ACTIVE) {
            std::shared_ptr<Command> command = infoStruct->prot.receiveCommand();
            std::shared_ptr<MatchCommand> mc = std::dynamic_pointer_cast<MatchCommand>(command);
            if (mc->getType() == NEW_MATCH) {
                createNewMatch(mc->getNrPlayers(), mc->getMatchName(), mc->getMapName());
            } else if (mc->getType() == JOIN) {
                joinMatch(mc->getMatchName());
            } else if (mc->getType() == REFRESH) {
                refresh();
            }
        }
    } catch (const ClosedSocket& e){
        std::cout << "Reciever: Se ha cerrado la conexion\n";
        kill();
        return;
    } catch (const std::exception& e){
        std::cout << "Error inesperado" << e.what() << std::endl;
        kill();
        return;
    }
    
} 


void ConnectingUser::createNewMatch(int numberPlayers, std::string matchName, std::string mapName) {

    MapsLoader mapsLoader(CONFIG.getMapsFile());
    std::vector<std::string> mapNames = mapsLoader.getMapsNames();
    Map map = mapsLoader.loadMap(mapName);
    std::vector<WormDTO> worms = createWorms(map.worms);
    std::vector<BeamDTO> beams = map.beams;

    std::vector<Team> teams = createTeams(worms, numberPlayers);

    std::shared_ptr<Queue<std::shared_ptr<InfoStruct>>> infoQueue = std::make_shared<Queue<std::shared_ptr<InfoStruct>>>();
    infoQueue->push(infoStruct);
    
    std::shared_ptr<GameMap> gameMap = std::make_shared<GameMap>(GameMap(0, numberPlayers, mapName, beams, worms));
    std::shared_ptr<MatchesStruct> matchStruct = std::make_shared<MatchesStruct>(teams, matchName, gameMap, playing, infoQueue);

    int code = matchesMonitor.addMatchStruct(matchName, matchStruct);
    infoStruct->prot.sendAllOk(code);
    if (code == ERROR) {
        return;
    }
    matchesMonitor.startMatch(matchName);    
    this->status = INACTIVE;
}


void ConnectingUser::joinMatch(std::string matchName) {

    // checkear que tenga espacio: si no existe manda 1 y si existe manda 0
    int code = matchesMonitor.joinMatch(matchName, infoStruct);
    infoStruct->prot.sendAllOk(code);
    if (code == ERROR) {
        return;
    }
    this->status = INACTIVE;
}



void ConnectingUser::refresh() {
    GameInfo info(matchesMonitor.showMatchesAvailable());
    infoStruct->prot.sendInfo(&info);
}


std::vector<Team> ConnectingUser::createTeams(std::vector<WormDTO>& worms, int numberOfPlayers) {
    std::vector<Team> teams;
    for(int id = 0; id < numberOfPlayers; id++){
        Team team(id);
        teams.push_back(team);
    }
    int currentTeam = 0;
    for(size_t i = 0; i < worms.size(); i++){
        teams[currentTeam].addWorm(worms[i].getId());
        worms[i].setTeam(currentTeam);
        currentTeam = (currentTeam + 1) % numberOfPlayers;
    }
    
    if(currentTeam == 0) return teams;

    for (; currentTeam < numberOfPlayers; currentTeam++){
        std::vector<int> teamWormsIDs = teams[currentTeam].getWormIDs();
        for(size_t i = 0; i < teamWormsIDs.size(); i++){
            worms[teamWormsIDs[i]].addHealth(CONFIG.getWormAdditionalHealth());
        }
    }

    return teams;
}

std::vector<WormDTO> ConnectingUser::createWorms(std::vector<WormPosition> wormsPositions){
    std::vector<WormDTO> worms;
    for(size_t i = 0; i < wormsPositions.size(); i++){
        WormDTO worm(i, STARTING_DIRECTON, STARTING_TEAM, CONFIG.getWormInitialHealth(), 0,
        0.0f, 0.0f, Position(wormsPositions[i].x, wormsPositions[i].y), STARTING_WEAPONS);
        worms.push_back(worm);
    }
    return worms;
}
    
bool ConnectingUser::isActive() {
    return status == ACTIVE;
}

void ConnectingUser::kill() {
    infoStruct->prot.boom();
    this->status = INACTIVE;
}

ConnectingUser::~ConnectingUser() {}
