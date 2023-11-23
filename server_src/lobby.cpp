#include "lobby.h"
#include "game_loop.h"
#include "match_starter.h"
#include "status_broadcaster.h"
#include <string>
#include "../game_src/constants_game.h"
#include "../game_src/worm_dto.h"
#include "../game_src/beam_dto.h"
#include "../game_src/game_map.h"
#include <memory>


Lobby::Lobby(const std::string& hostname, int numberOfPlayers, std::string mapName, bool* playing) 
: hostname(hostname), skt(hostname.c_str()), mapName(mapName), commandQueue(90), playing(playing) {
    this->numberOfPlayers = numberOfPlayers;
}

std::vector<WormDTO> Lobby::createWorms(std::vector<WormPosition> wormsPositions) {
    std::vector<WormDTO> worms;
    for(size_t i = 0; i < wormsPositions.size(); i++){
        WormDTO worm(i, STARTING_DIRECTON, STARTING_TEAM, CONFIG.getWormInitialHealth(),
         Position(wormsPositions[i].x, wormsPositions[i].y), STARTING_WEAPONS);
        worms.push_back(worm);
    }
    return worms;
}

std::vector<Team> Lobby::createTeams(std::vector<WormDTO>& worms) {
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
    
void Lobby::run() {

    while (true) {
        Socket peer = skt.accept();
                    
        std::shared_ptr<InfoStruct>infoStruct = std::make_shared<InfoStruct>(std::move(peer));
        // uso el inof para comunicarme con el cliente pre generar un player 
        // Orden de msgs:
            // send -> GameInfo con los mapas disponibles y las partidas available
            // receive -> NewMatch o JoinMatch
                // en NewMatch : recibir el map name y el match name
                // en JoinMatch : recibir el match name

        // Comando -> New Match 
            
            // -> MatchName 

            // Comando SelectMap -> 

            MapsLoader mapsLoader(CONFIG.getMapsFile());
            std::vector<std::string> mapNames = mapsLoader.getMapsNames();
            Map map = mapsLoader.loadMap(mapName);
            std::vector<WormDTO> worms = createWorms(map.worms);
            std::vector<BeamDTO> beams = map.beams;

            std::vector<Team> teams = createTeams(worms);

            // se deberian parsear los archivos con los mapas
            std::vector<std::string> maps = {"merge speedrun"};


            Queue<std::shared_ptr<InfoStruct>>* infoQueue = new Queue<std::shared_ptr<InfoStruct>>();
            infoQueue->push(infoStruct);
            
            std::shared_ptr<GameMap> gameMap = std::make_shared<GameMap>(GameMap(0, numberOfPlayers, mapName, beams, worms));
            MatchStarter* matchStarter =  new MatchStarter(teams, infoQueue, "un nombre", gameMap, playing);
            MatchesStruct* matchStruct = new MatchesStruct(matchStarter, infoQueue);

            matches["un nombre"] = matchStruct;

        // Comando -> Join Match -> MatchName
            Queue<std::shared_ptr<InfoStruct>>* infoQueueMatch = matches["un nombre"]->infoQueue;
            std::shared_ptr<InfoStruct>infoJoiner = std::make_shared<InfoStruct>(std::move(peer));
            infoQueueMatch->push(infoJoiner);

    }

    // int idPlayer = 0;

    // StatusBroadcaster statusBroadcaster;

    // while(idPlayer < numberOfPlayers) {
    //     try {
    //         Socket peer = skt.accept();
    //         std::shared_ptr<GameMap> gameMap =std::make_shared<GameMap>(GameMap(idPlayer, numberOfPlayers, "aloha", beams, worms));
    //         Player* player = new Player(std::move(peer), commandQueue, gameMap);
    //         statusBroadcaster.addPlayer(idPlayer, player->getPlayerQueue());
    //         player->start();

    //         reapDead();
    //         players.push_back(player);
    //         idPlayer++;
    //     } catch (std::exception& e) {
    //         std::cout << "Error in lobby: " << e.what() << std::endl;
    //     }
    // }
    // // momento eleccion Mapa
    // std::shared_ptr<GameMap> gameMap = std::make_shared<GameMap>(GameMap(0, numberOfPlayers, "aloha", beams, worms));
    // // Inicializar el GameLoop 
    // bool loopActive = true;
    // GameLoop gameLoop(commandQueue, statusBroadcaster, gameMap, teams, &loopActive);
    // gameLoop.start();


    // while (*playing) {
    //     reapDead();
    // }

    // loopActive = false;

    killAll();

    // gameLoop.join();
}

void Lobby::reapDead() {
    players.remove_if([](Player* player) {
        if (!player->isAlive()) {
            player->join();
            delete player;
            return true;
        } else {
            return false;
        }
    });
}

void Lobby::killAll() {
    for (auto& player : players ) {
        if (player->isAlive()) {
            player->kill();
        }
        player->join();
        delete player;
    }
    players.clear();
}

Lobby::~Lobby() {killAll();}
