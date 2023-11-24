#include "connecting_user.h"

ConnectingUser::ConnectingUser(std::shared_ptr<InfoStruct> infoStruct, MatchesMonitor& matchesMonitor) : 
infoStruct(infoStruct), matchesMonitor(matchesMonitor), status(ACTIVE) {}


void ConnectingUser::run() {
    // uso el inof para comunicarme con el cliente pre generar un player 
    // Orden de msgs:
        // send -> GameInfo con los mapas disponibles y las partidas available
        // receive -> NewMatch o JoinMatch
            // en NewMatch : recibir el map name y el match name
            // en JoinMatch : recibir el match name

    std::string mapName = "medium";
    int numberOfPlayers = 1;
    bool playing = true;

    // // // // // // // // // // //

    MapsLoader mapsLoader(CONFIG.getMapsFile());
    std::vector<std::string> mapNames = mapsLoader.getMapsNames();
    Map map = mapsLoader.loadMap(mapName);
    std::vector<WormDTO> worms = createWorms(map.worms);
    std::vector<BeamDTO> beams = map.beams;

    std::vector<Team> teams = createTeams(worms, numberOfPlayers);

    // se deberian parsear los archivos con los mapas
    std::vector<std::string> maps = {"merge speedrun"};


    Queue<std::shared_ptr<InfoStruct>>* infoQueue = new Queue<std::shared_ptr<InfoStruct>>();
    infoQueue->push(infoStruct);
    
    std::shared_ptr<GameMap> gameMap = std::make_shared<GameMap>(GameMap(0, numberOfPlayers, mapName, beams, worms));
    MatchStarter* matchStarter =  new MatchStarter(teams, infoQueue, "un nombre", gameMap, &playing);
    MatchesStruct* matchStruct = new MatchesStruct(mapName, matchStarter, infoQueue);


    // matches["un nombre"] = matchStruct;

    // Comando -> Join Match -> MatchName
            // Queue<std::shared_ptr<InfoStruct>>* infoQueueMatch = matches["un nombre"]->infoQueue;
            // std::shared_ptr<InfoStruct>infoJoiner = std::make_shared<InfoStruct>(std::move(peer));
            // infoQueueMatch->push(infoJoiner);


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
        WormDTO worm(i, STARTING_DIRECTON, STARTING_TEAM, CONFIG.getWormInitialHealth(),
         Position(wormsPositions[i].x, wormsPositions[i].y), STARTING_WEAPONS);
        worms.push_back(worm);
    }
    return worms;
}
    
bool ConnectingUser::isActive() {
    return status == ACTIVE;
}