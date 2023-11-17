#ifndef RECEIVER_SERVER_H
#define RECEIVER_SERVER_H

#include "../shared_src/thread.h"
#include "../shared_src/queue.h"
#include "../shared_src/protocol.h"

class ServerReceiver : public Thread {

private:
    Protocol& protocol;
    Queue<Command*>& commandsQueue;
    bool& talking;
    // has the only queue of the game thread :)
public:
    ServerReceiver(Protocol& protocol, Queue<Command*>& commandsQueue, bool& talking);
    ~ServerReceiver();
    void run() override;

};
#endif