#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include <string>

class Protocol;
class GameWorld;

#define UNUSED(x) (void)(x)
class Command {

private:
    int team;
    int wormID;
public:
    Command(int wormID) : wormID(wormID) {}
    virtual ~Command() {}
    virtual bool executeCommand(GameWorld&, bool* cheatOn) {
        std::cout << "exec mother class\n";
        *cheatOn = *cheatOn;
        return true;
    }
    virtual std::string executeCommand() {
        std::cout << "exec mother class\n";
        return "";
    }
    virtual void send(Protocol& protocol) = 0;
    virtual int getID() = 0;
};
#endif
