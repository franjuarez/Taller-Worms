#include "client_lobby.h"
#include "../game_src/commands/command.h"
#include "../game_src/commands/match_command.h"
#include "../game_src/constants_game.h"
#include "../game_src/game_info.h"

#define NM "nm"
#define JM "jm"
#define R "r"

ClientLobby::ClientLobby(std::shared_ptr<InfoStruct> infoStruct) : infoStruct(infoStruct) {}


void ClientLobby::run() {

    showMatches();

    std::string userInput;
    while(true) {
        std::cin >> userInput;

        std::string matchName;
        std::string mapName;
        int numberPlayers;

        if (userInput == NM) {
            std::cin >> numberPlayers;
            std::cin >> matchName;
            std::cin >>mapName;

            createNewMatch(numberPlayers, matchName, mapName);
            return;

        } else if (userInput == JM) {
            std::cin >> matchName;
            joinMatch(matchName);
            return;
        } else if (userInput == R) {
            refresh();
            showMatches();
        } else {
            std::cout << "Invalid Command\n";
        }
    }
}


void ClientLobby::createNewMatch( int nrPlayers, std::string matchName, std::string mapName) {
    MatchCommand* mc = new MatchCommand(NEW_MATCH, nrPlayers, matchName, mapName);
    mc->send(infoStruct->prot);
}

void ClientLobby::joinMatch(std::string matchName) {
    int numberPlayers = 0;
    std::string mapName = "";
    MatchCommand* mc = new MatchCommand(JOIN, numberPlayers, matchName, mapName);
    mc->send(infoStruct->prot);
}

void ClientLobby::refresh() {
    int numberPlayers = 0;
    std::string mapName = "";
    std::string matchName = "";
    MatchCommand* mc = new MatchCommand(REFRESH, numberPlayers, matchName, mapName);
    mc->send(infoStruct->prot);
}


void ClientLobby::showMatches() {
    std::shared_ptr<Serializable>gameDynamic(infoStruct->prot.receiveSerializable());
    std::shared_ptr<GameInfo> gs = std::dynamic_pointer_cast<GameInfo>(gameDynamic);
    std::cout<< "Showing Available Matches\n";
    std::map<std::string, std::string> matchesAvailable = gs->getMatchesAvailable();
    for (auto& match : matchesAvailable) {
        std::cout << "Match: " << match.first << std::endl;
        std::cout << "  Map: " << match.second << std::endl;
    }
}


ClientLobby::~ClientLobby() {}