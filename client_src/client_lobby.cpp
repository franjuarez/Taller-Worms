#include "client_lobby.h"
#include "../game_src/commands/command.h"
#include "../game_src/commands/match_command.h"
#include "../game_src/constants_game.h"
#include "../game_src/game_info.h"
#include "../ui_src/game_view.h"


#define NM "nm"
#define JM "jm"
#define R "r"

ClientLobby::ClientLobby(const std::string& hostname, const std::string& servname) : infoStruct(std::make_shared<InfoStruct>(hostname, servname)) {}


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


    GameView gv(infoStruct);
    gv.start();
    gv.join();
}

void ClientLobby::joinMatch(std::string matchName) {
    int numberPlayers = 0;
    std::string mapName = "";
    MatchCommand* mc = new MatchCommand(JOIN, numberPlayers, matchName, mapName);
    mc->send(infoStruct->prot);

    GameView gv(infoStruct);
    gv.start();
    gv.join();
}

void ClientLobby::refresh() {
    int numberPlayers = 0;
    std::string mapName = "";
    std::string matchName = "";
    MatchCommand* mc = new MatchCommand(REFRESH, numberPlayers, matchName, mapName);
    mc->send(infoStruct->prot);
}


std::map<std::string, std::string> ClientLobby::getAvailableMatches() {
    std::shared_ptr<Serializable>gameDynamic(infoStruct->prot.receiveSerializable());
    std::shared_ptr<GameInfo> gs = std::dynamic_pointer_cast<GameInfo>(gameDynamic);
    return gs->getMatchesAvailable();
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