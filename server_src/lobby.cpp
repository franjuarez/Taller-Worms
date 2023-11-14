#include "lobby.h"
#include "game_loop.h"
#include "status_broadcaster.h"

#include "../game_src/worm_dto.h"
#include "../game_src/beam_dto.h"
#include "../game_src/game_map.h"

//Lobby::Lobby(Socket& skt, int AMOUNT_OF_PLAYERS) : , skt(skt), commandQueue(90) {
//    this->AMOUNT_OF_PLAYERS = AMOUNT_OF_PLAYERS;
//}

Lobby::Lobby(const std::string& hostname, int numberOfPlayers, std::string mapName) : hostname(hostname), skt(hostname.c_str()), mapName(mapName), commandQueue(90) {
    this->numberOfPlayers = numberOfPlayers;
}

void Lobby::run() {

    // YA TENGO EL NRO DE PLAYERS -> YA ASIGNO A LOS GUSANOS A SUS TEAMS

    std::vector<BeamDTO> beams;
    std::vector<WormDTO> worms;
    Position pos(9.7, 11.0);
    Position pos2(9.89, 12.1);
    worms.push_back(WormDTO(2, 0, 1, 100, pos, {}));
    worms.push_back(WormDTO(1, 0, 2,  100, pos2, {}));

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



    // se deberian parsear los archivos con los mapas
    std::vector<std::string> maps = {"merge speedrun"};
    int idPlayer = 0;

    StatusBroadcaster statusBroadcaster;

    while(idPlayer < numberOfPlayers) {
        try {
            Socket peer = skt.accept();
            idPlayer++;
            GameMap* map = new GameMap(idPlayer, "aloha", beams, worms);
            Player* player = new Player(std::move(peer), commandQueue, map);
            // magic happens
            statusBroadcaster.addPlayer(idPlayer, player->getPlayerQueue());
            player->start();

            reapDead();
            players.push_back(player);
        } catch (...) {
            // pasan mas cosas 
        }
    }
    // momento eleccion Mapa
    GameMap* map = new GameMap(0, "aloha", beams, worms);
    // Inicializar el GameLoop 
    GameLoop gameLoop(commandQueue, statusBroadcaster, map);
    gameLoop.start();

    killAll();
}

void Lobby::reapDead() {}

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

Lobby::~Lobby() {}