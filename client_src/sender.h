#ifndef SENDER_H
#define SENDER_H

#include "../shared_src/thread.h"
#include "../shared_src/queue.h"
#include "../shared_src/protocol.h"
#include "../game_src/commands/command.h"

#include <iostream>
#include <string>

struct ClientClosed : public std::runtime_error {
    ClientClosed() : std::runtime_error("Client is closed") {} 
}; 

class Sender : public Thread {

private:
    Protocol& protocol;
    Queue<std::shared_ptr<Command>>& commandsQueue;
    bool& keepTalking;
public:
    Sender(Protocol& protocol, Queue<std::shared_ptr<Command>>& q, bool& keepTalking);
    void run() override;
    ~Sender();
};
#endif
