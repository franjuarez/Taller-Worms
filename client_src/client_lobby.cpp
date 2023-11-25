#include "client_lobby.h"
#include "../game_src/commands/command.h"
#include "../game_src/commands/match_command.h"
#include "../game_src/constants_game.h"
#include "../game_src/game_info.h"

#define NM "nm"
#define JM "jm"
#define R "r"

ClientLobby::ClientLobby(const std::string& hostname, const std::string& servname) : prot(hostname, servname) {}


void ClientLobby::run() {

    showMatches();

    std::string userInput;
    while(true) {
        std::cin >> userInput;

        std::string matchName = "";
        std::string mapName = "";
        int numberPlayers = 0;

        if (userInput == NM) {
            std::cin >> numberPlayers;
            std::cin >> matchName;
            std::cin >>mapName;

            MatchCommand* mc = new MatchCommand(NEW_MATCH, numberPlayers, matchName, mapName);
            mc->send(prot);
            return;

        } else if (userInput == JM) {
            std::cin >> matchName;
            MatchCommand* mc = new MatchCommand(JOIN, numberPlayers, matchName, mapName);
            mc->send(prot);
            return;
        } else if (userInput == R) {
            MatchCommand* mc = new MatchCommand(REFRESH, numberPlayers, matchName, mapName);
            mc->send(prot);
            showMatches();
        } else {
            std::cout << "Invalid Command\n";
        }
    }
}

void ClientLobby::showMatches() {
    std::shared_ptr<Serializable>gameDynamic(prot.receiveSerializable());
    std::shared_ptr<GameInfo> gs = std::dynamic_pointer_cast<GameInfo>(gameDynamic);
    std::cout<< "Showing Available Matches\n";
    std::map<std::string, std::string> matchesAvailable;
    for (auto& match : matchesAvailable) {
        std::cout << "Match: " << match.first << std::endl;
        std::cout << "  Map: " << match.second << std::endl;
    }
    // std::cout << gs->getMatchesAvailable().size() << std::endl;
}


ClientLobby::~ClientLobby() {}